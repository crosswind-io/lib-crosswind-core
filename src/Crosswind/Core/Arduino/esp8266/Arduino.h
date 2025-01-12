#pragma once

#if defined(ESP8266)

#include <stdint.h>

#include <functional>

#include "esp8266.h"

#define LOW               0x0
#define HIGH              0x1

// GPIO FUNCTIONS
#define INPUT             0x01
#define OUTPUT            0x02
#define PULLUP            0x04
#define INPUT_PULLUP      0x05
#define PULLDOWN          0x08
#define INPUT_PULLDOWN    0x09
#define OPEN_DRAIN        0x10
#define OUTPUT_OPEN_DRAIN 0x12
#define SPECIAL           0xF0
#define FUNCTION_1        0x00
#define FUNCTION_2        0x20
#define FUNCTION_3        0x40
#define FUNCTION_4        0x60
#define FUNCTION_5        0x80
#define FUNCTION_6        0xA0
#define ANALOG            0xC0

// Interrupt Modes
#define DISABLED  0x00
#define RISING    0x01
#define FALLING   0x02
#define CHANGE    0x03
#define ONLOW     0x04
#define ONHIGH    0x05
#define INTR_WE   0x08
#define ONLOW_WE  (ONLOW | INTR_WE) // 0x0C
#define ONHIGH_WE (ONHIGH | INTR_WE) // 0x0D

// Pauses the program for the amount of time (in milliseconds) specified as parameter.
// (There are 1000 milliseconds in a second.)
void delay(unsigned long ms);

// Returns the number of milliseconds since the board began running the current program.
// This number will overflow (go back to zero), after approximately 50 days.
unsigned long millis();

// Returns the number of microseconds since the board began running the current program.
// This number will overflow (go back to zero), after approximately 70 minutes.
unsigned long micros();

// Configures the specified pin to behave either as an input or an output.
void pinMode(uint8_t pin, uint8_t mode);

// Write a HIGH or a LOW value to a digital pin.
void digitalWrite(uint8_t pin, uint8_t val);

// Reads the value from a specified digital pin, either HIGH or LOW.
int digitalRead(uint8_t pin);

// Attaches an input pin to an interrupt.
void attachInterrupt(uint8_t pin, std::function<void(void)> intRoutine, int mode);

// Turns off the given interrupt.
void detachInterrupt(uint8_t pin);

// Gets an interrupt for a digital pin.
#define digitalPinToInterrupt(p)    (((p)<17)?(p):-1)

// Sets up a PWM channel, frequency, and resolution.
void ledcSetup(uint8_t channel, double freq, uint8_t resolution_bits);

// Binds the LEDC channel to a specified IO port for output.
void ledcAttachPin(uint8_t pin, uint8_t channel);

// Writes a duty cycle percentage to a channel.
void ledcWrite(uint8_t channel, uint32_t duty);

// TODO

#endif // ESP8266
