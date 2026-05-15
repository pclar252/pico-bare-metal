#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"

#define ALARM_NUM   0
#define ALARM_IRQ   TIMER_IRQ_0
#define INTERVAL_US 500000u
#define LED_PIN     25

static volatile uint32_t tick_count = 0;

static void alarm_irq_handler(void) {
    hw_clear_bits(&timer_hw->intr, 1u << ALARM_NUM);

    tick_count++;
    gpio_xor_mask(1u << LED_PIN);

    timer_hw->alarm[ALARM_NUM] = timer_hw->timerawl + INTERVAL_US;
}

int main(void) {
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    hardware_alarm_claim(ALARM_NUM);
    irq_set_exclusive_handler(ALARM_IRQ, alarm_irq_handler);
    irq_set_enabled(ALARM_IRQ, true);

    hw_set_bits(&timer_hw->inte, 1u << ALARM_NUM);
    timer_hw->alarm[ALARM_NUM] = timer_hw->timerawl + INTERVAL_US;

    printf("Timer example running\n");

    while (true) {
        printf("ticks: %lu\n", (unsigned long)tick_count);
        sleep_ms(1000);
    }
}
