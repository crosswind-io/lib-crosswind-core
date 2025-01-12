#pragma once

#if defined(ESP8266)

#define TASK_PRIO_ARDUINO_LOOP      5
#define TASK_PRIO_GPIO_INTERRUPTS   10

#if !defined(ARDUINO_LOOP_STACK_SIZE)
  #define ARDUINO_LOOP_STACK_SIZE   8192
#endif

extern "C" void app_main();

#include "driver/gpio.h"

typedef void (*GPIOInterruptFunction_t)(gpio_num_t);

void gpio_enable_interrupts(GPIOInterruptFunction_t gpio_intr_handler);
void gpio_add_interrupt(gpio_num_t gpio_num);
void gpio_remove_interrupt(gpio_num_t gpio_num);

#endif // ESP8266
