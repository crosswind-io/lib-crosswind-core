#if defined(ESP8266)

#include "Stream.h"
#include "Arduino.h"

#define NO_SKIP_CHAR  1  // a magic char not found in a valid ASCII numeric field

Stream::Stream() {
}

Stream::~Stream() {
}

// sets maximum milliseconds to wait for stream data, default is 1 second
void Stream::setTimeout(unsigned long timeout) {
    _timeout = timeout;
}

unsigned long Stream::getTimeout() {
  return _timeout;
}

// reads data from the stream until the target string is found
bool Stream::find(const char* target) {
  return findUntil(target, strlen(target), nullptr, 0);
}

// reads data from the stream until the target string is found
bool Stream::find(uint8_t* target) {
  return find((char*)target);
}

// returns true if target string is found, false if timed out (see setTimeout)
bool Stream::find(const char *target, size_t length) {
  return findUntil(target, length, nullptr, 0);
}

bool Stream::find(const uint8_t* target, size_t length) {
  return find((char*)target, length);
}

// returns true if target string is found, false if timed out
bool Stream::find(char target) {
  return find(&target, 1);
}

// same as find but search ends if the terminator string is found
bool Stream::findUntil(const char* target, const char* terminator) {
  return findUntil(target, strlen(target), terminator, strlen(terminator));
}

bool Stream::findUntil(const uint8_t* target, const char* terminator) {
  return findUntil((char*)target, terminator);
}

// same as above but search ends if the terminator string is found
bool Stream::findUntil(const char* target, size_t targetLen, const char* terminator, size_t termLen) {
  if (terminator == nullptr) {
    MultiTarget t[1] = {{target, targetLen, 0}};
    return findMulti(t, 1) == 0 ? true : false;
  } else {
    MultiTarget t[2] = {{target, targetLen, 0}, {terminator, termLen, 0}};
    return findMulti(t, 2) == 0 ? true : false;
  }
}

bool Stream::findUntil(const uint8_t* target, size_t targetLen, const char* terminator, size_t termLen) {
  return findUntil((char*)target, targetLen, terminator, termLen);
}

// read chars from stream into buffer
size_t Stream::readBytes(char* buffer, size_t length) {
  size_t count = 0;

  while(count < length) {
    int c = timedRead();
    if (c < 0) {
      break;
    }
    *buffer++ = (char) c;
    count++;
  }

  return count;
}

size_t Stream::readBytes(uint8_t* buffer, size_t length) {
    return readBytes((char*)buffer, length);
}

// same as readBytes with terminator character
size_t Stream::readBytesUntil(char terminator, char* buffer, size_t length) {
  if (length < 1) {
    return 0;
  }

  size_t index = 0;
  while (index < length) {
    int c = timedRead();
    if (c < 0 || c == terminator) {
      break;
    }
    *buffer++ = (char)c;
    index++;
  }

  return index;
}

size_t Stream::readBytesUntil(char terminator, uint8_t* buffer, size_t length) {
  return readBytesUntil(terminator, (char*)buffer, length);
}

// returns the first valid (long) integer value from the current position.
// initial characters that are not digits (or the minus sign) are skipped
// function is terminated by the first character that is not a digit.
long Stream::parseInt() {
  // terminate on first non-digit character (or timeout)
  return parseInt(NO_SKIP_CHAR);
}

// as above but a given skipChar is ignored
// this allows format characters (typically commas) in values to be ignored
long Stream::parseInt(char skipChar) {
  bool isNegative = false;
  long value = 0;
  int c;

  c = peekNextDigit();

  // ignore non numeric leading characters
  if (c < 0) {
    // zero returned if timeout
    return 0;
  }

  do {
    if (c == skipChar) {
      // ignore this character
    } else if (c == '-') {
      isNegative = true;
    } else if (c >= '0' && c <= '9') {
      // is c a digit?
      value = value * 10 + c - '0';
    }

    // consume the character we got with peek
    read();
    c = timedPeek();
  } while((c >= '0' && c <= '9') || c == skipChar);

  if (isNegative) {
    value = -value;
  }

  return value;
}

// as parseInt but returns a floating point value
float Stream::parseFloat() {
  return parseFloat(NO_SKIP_CHAR);
}

// as above but the given skipChar is ignored
// this allows format characters (typically commas) in values to be ignored
float Stream::parseFloat(char skipChar) {
  bool isNegative = false;
  bool isFraction = false;
  long value = 0;
  int c;
  float fraction = 1.0;

  c = peekNextDigit();

  // ignore non numeric leading characters
  if (c < 0) {
    // zero returned if timeout
    return 0;
  }

  do {
    if (c == skipChar) {
      // ignore
    } else if(c == '-') {
      isNegative = true;
    } else if(c == '.') {
      isFraction = true;
    } else if(c >= '0' && c <= '9') {
      // is c a digit?
      value = value * 10 + c - '0';
      if (isFraction) {
        fraction *= 0.1;
      }
    }

    // consume the character we got with peek
    read();
    c = timedPeek();
  } while((c >= '0' && c <= '9') || c == '.' || c == skipChar);

  if (isNegative) {
    value = -value;
  }

  if (isFraction) {
    return value * fraction;
  } else {
    return value;
  }
}

// This allows you to search for an arbitrary number of strings.
// Returns index of the target that is found first or -1 if timeout occurs.
int Stream::findMulti(struct MultiTarget* targets, int tCount) {
  // any zero length target string automatically matches and would make
  // a mess of the rest of the algorithm.
  for (struct MultiTarget *t = targets; t < targets+tCount; ++t) {
    if (t->len <= 0) {
      return t - targets;
    }
  }

  while (1) {
    int c = timedRead();
    if (c < 0) {
      return -1;
    }

    for (struct MultiTarget *t = targets; t < targets+tCount; ++t) {
      // the simple case is if we match, deal with that first.
      if (c == t->str[t->index]) {
        if (++t->index == t->len) {
          return t - targets;
        } else {
          continue;
        }
      }

      // if not we need to walk back and see if we could have matched further
      // down the stream (ie '1112' doesn't match the first position in '11112'
      // but it will match the second position so we can't just reset the current
      // index to 0 when we find a mismatch.
      if (t->index == 0) {
        continue;
      }

      int origIndex = t->index;
      do {
        --t->index;
        // first check if current char works against the new current index
        if (c != t->str[t->index]) {
          continue;
        }

        // if it's the only char then we're good, nothing more to check
        if (t->index == 0) {
          t->index++;
          break;
        }

        // otherwise we need to check the rest of the found string
        int diff = origIndex - t->index;
        size_t i;
        for (i = 0; i < t->index; ++i) {
          if (t->str[i] != t->str[i + diff]) {
            break;
          }
        }

        // if we successfully got through the previous loop then our current
        // index is good.
        if (i == t->index) {
          t->index++;
          break;
        }

        // otherwise we just try the next index
      } while (t->index);
    }
  }

  // unreachable
  return -1;
}

// private method to read stream with timeout
int Stream::timedRead() {
  int c;
  _startMillis = millis();
  do {
    c = read();
    if(c >= 0) {
      return c;
    }
  } while(millis() - _startMillis < _timeout);

  // -1 indicates timeout
  return -1;
}

// private method to peek stream with timeout
int Stream::timedPeek() {
  int c;
  _startMillis = millis();
  do {
    c = peek();
    if(c >= 0) {
      return c;
    }
  } while(millis() - _startMillis < _timeout);

  // -1 indicates timeout
  return -1;
}

// returns peek of the next digit in the stream or -1 if timeout
// discards non-numeric characters
int Stream::peekNextDigit() {
  int c;
  while(1) {
    c = timedPeek();
    if(c < 0) {
      // timeout
      return c;
    }
    if(c == '-') {
      return c;
    }
    if(c >= '0' && c <= '9') {
      return c;
    }

    // discard non-numeric
    read();
  }
}

#endif // ESP8266
