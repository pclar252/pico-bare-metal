#include <stdbool.h>

#include <emblib/gpio.h>
#include <emblib/nvic.h>
#include <emblib/sio.h>
#include <emblib/timer.h>

#define ALARM_NUM 0
#define ALARM_IRQ EM_TIMER0_ALARM0
#define INTERVAL_US 500000u
#define LED_PIN 25

static void alarm_irq_handler(void) {
  em_timer0_intr_clr(ALARM_NUM);

  em_sio_gpio_out_xor(LED_PIN);

  em_timer0_schedule_rel(ALARM_NUM, INTERVAL_US);
}

int main(void) {
  em_gpio_init(LED_PIN, EM_SIO_0);
  em_gpio_set_dir(LED_PIN, EM_GPIO_OUT);

  em_nvic_set_handler(ALARM_IRQ, alarm_irq_handler);
  em_nvic_enable(ALARM_IRQ);

  em_timer0_inte_set(ALARM_NUM);
  em_timer0_schedule_rel(ALARM_NUM, INTERVAL_US);

  while (true) {
  }
}
