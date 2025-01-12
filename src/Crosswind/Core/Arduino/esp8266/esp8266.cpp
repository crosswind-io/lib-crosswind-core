#if defined(ESP8266)

#include "esp8266.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#define XSTR(x) STR(x)
#define STR(x) #x

#pragma message("ARDUINO_LOOP_STACK_SIZE=" XSTR(ARDUINO_LOOP_STACK_SIZE))

extern void setup();
extern void loop();

static void arduino_loop(void* arg) {
  while (true) {
    loop();
    vTaskDelay(10 / portTICK_RATE_MS);
  }
}

extern "C" void app_main() {
  setup();

  xTaskCreate(
    arduino_loop,
    "arduino_loop",
    ARDUINO_LOOP_STACK_SIZE,
    nullptr,
    TASK_PRIO_ARDUINO_LOOP,
    nullptr
  );
}

#define GPIO_INTR_QUEUE_PROCESSOR_STACK_SIZE    1024

static GPIOInterruptFunction_t _gpio_intr_handler = nullptr;
static xQueueHandle _gpio_intr_queue = nullptr;

static void gpio_isr_handler(void* arg) {
  uint32_t gpio_num = (uint32_t)arg;
  xQueueSendFromISR(_gpio_intr_queue, &gpio_num, nullptr);
}

static void gpio_intr_queue_processor(void* arg) {
  uint32_t gpio_num;

  while(true) {
    if (xQueueReceive(_gpio_intr_queue, &gpio_num, portMAX_DELAY)) {
      if (_gpio_intr_handler != nullptr) {
        _gpio_intr_handler(static_cast<gpio_num_t>(gpio_num));
      }
    }
  }
}

void gpio_enable_interrupts(GPIOInterruptFunction_t gpio_intr_handler) {
  if (_gpio_intr_queue == nullptr) {
    // store the GPIO interrupt handler
    _gpio_intr_handler = gpio_intr_handler;

    // setup the GPIO interrupt queue
    _gpio_intr_queue = xQueueCreate(10, sizeof(uint32_t));

    // start the GPIO interrupt queue processor
    xTaskCreate(
      gpio_intr_queue_processor,
      "gpio_intr_queue_processor",
      GPIO_INTR_QUEUE_PROCESSOR_STACK_SIZE,
      nullptr,
      TASK_PRIO_GPIO_INTERRUPTS,
      nullptr
    );

    // install the GPIO ISR
    gpio_install_isr_service(0);
  }
}

void gpio_add_interrupt(gpio_num_t gpio_num) {
  gpio_isr_handler_add(gpio_num, gpio_isr_handler, (void*)((uint32_t)gpio_num));
}

void gpio_remove_interrupt(gpio_num_t gpio_num) {
  gpio_isr_handler_remove(gpio_num);
}

#endif // ESP8266
