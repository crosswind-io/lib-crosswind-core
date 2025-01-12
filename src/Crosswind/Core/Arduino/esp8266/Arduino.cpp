#if defined(ESP8266)

#include "Arduino.h"

#include <string.h>
#include <sys/time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include <map>

// Pauses the program for the amount of time (in milliseconds) specified as parameter.
// (There are 1000 milliseconds in a second.)
void delay(unsigned long ms) {
  usleep(ms * 1000); // vTaskDelay(ms / portTICK_RATE_MS);
}

static struct timeval gtod0 = { 0, 0 };

// Returns the number of milliseconds since the board began running the current program.
// This number will overflow (go back to zero), after approximately 50 days.
unsigned long millis() {
  timeval time;
  gettimeofday(&time, NULL);
  if (gtod0.tv_sec == 0)
    memcpy(&gtod0, &time, sizeof gtod0);
  return ((time.tv_sec - gtod0.tv_sec) * 1000) + ((time.tv_usec - gtod0.tv_usec) / 1000);

  //return (xTaskGetTickCount() * portTICK_RATE_MS);
}

// Returns the number of microseconds since the board began running the current program.
// This number will overflow (go back to zero), after approximately 70 minutes.
unsigned long micros() {
  timeval time;
  gettimeofday(&time, NULL);
  if (gtod0.tv_sec == 0)
    memcpy(&gtod0, &time, sizeof gtod0);
  return ((time.tv_sec - gtod0.tv_sec) * 1000000) + time.tv_usec - gtod0.tv_usec;
}

// Configures the specified pin to behave either as an input or an output.
void pinMode(uint8_t pin, uint8_t mode) {
  gpio_config_t io_conf;
  memset(&io_conf, 0x00, sizeof(gpio_config_t));

  if (mode & INPUT) {
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.pull_up_en = ((mode & PULLUP) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE);
    io_conf.pull_down_en = ((mode & PULLDOWN) ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE);
  } else if (mode & OUTPUT) {
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = ((mode & OPEN_DRAIN) ? GPIO_MODE_OUTPUT_OD : GPIO_MODE_OUTPUT);
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.pull_up_en = ((mode & PULLUP) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE);
    io_conf.pull_down_en = ((mode & PULLDOWN) ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE);
  }

  gpio_config(&io_conf);
}

// Write a HIGH or a LOW value to a digital pin.
void digitalWrite(uint8_t pin, uint8_t val) {
  gpio_set_level(static_cast<gpio_num_t>((int)pin), val);
}

// Reads the value from a specified digital pin, either HIGH or LOW.
int digitalRead(uint8_t pin) {
  return gpio_get_level(static_cast<gpio_num_t>((int)pin));
}

std::map<uint8_t, std::function<void(void)>> _gpio_intr_routines;

void _gpio_intr_handler(gpio_num_t gpio_num) {
  auto intr = _gpio_intr_routines.find(gpio_num);
  if (intr != _gpio_intr_routines.end()) {
    intr->second();
  }
}

gpio_int_type_t _gpio_intr_type(int mode) {
  gpio_int_type_t type = GPIO_INTR_DISABLE;
  switch (mode) {
    case RISING: type = GPIO_INTR_POSEDGE; break;
    case FALLING: type = GPIO_INTR_NEGEDGE; break;
    case CHANGE: type = GPIO_INTR_ANYEDGE; break;

    case ONLOW:
    case ONLOW_WE:
      type = GPIO_INTR_LOW_LEVEL;
    break;

    case ONHIGH:
    case ONHIGH_WE:
      type = GPIO_INTR_HIGH_LEVEL; break;

  }
  return type;
}

// Attaches an input pin to an interrupt.
void attachInterrupt(uint8_t pin, std::function<void(void)> intRoutine, int mode) {
  // enable interrupts (if not already enabled)
  gpio_enable_interrupts(_gpio_intr_handler);

  // save the interrupt routine
  _gpio_intr_routines.emplace(pin, intRoutine);

  // set the GPIO interrupt type and wakeup mode
  gpio_set_intr_type(static_cast<gpio_num_t>(pin), _gpio_intr_type(mode));
  if (mode & INTR_WE) {
    gpio_wakeup_enable(static_cast<gpio_num_t>(pin), _gpio_intr_type(mode));
  } else {
    gpio_wakeup_disable(static_cast<gpio_num_t>(pin));
  }

  // add the interrupt to the ISR
  gpio_add_interrupt(static_cast<gpio_num_t>(pin));
}

// Turns off the given interrupt.
void detachInterrupt(uint8_t pin) {
  // disable the GPIO interrupt type and wakeup mode
  gpio_set_intr_type(static_cast<gpio_num_t>(pin), GPIO_INTR_DISABLE);
  gpio_wakeup_disable(static_cast<gpio_num_t>(pin));

  // remove the interrupt from the ISR
  gpio_remove_interrupt(static_cast<gpio_num_t>(pin));

  // delete the interrupt routine
  _gpio_intr_routines.erase(pin);
}

// Sets up a PWM channel, frequency, and resolution.
void ledcSetup(uint8_t channel, double freq, uint8_t resolution_bits) {
  // https://github.com/StefanBruens/ESP8266_new_pwm
  // TODO
}

// Binds the LEDC channel to a specified IO port for output.
void ledcAttachPin(uint8_t pin, uint8_t channel) {
  // https://github.com/StefanBruens/ESP8266_new_pwm
  // TODO
}

// Writes a duty cycle percentage to a channel.
void ledcWrite(uint8_t channel, uint32_t duty) {
  // https://github.com/StefanBruens/ESP8266_new_pwm
  // TODO
}

#endif
