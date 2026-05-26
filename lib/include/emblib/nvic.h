#ifndef EMBLIB_NVIC_H
#define EMBLIB_NVIC_H

#include <stdint.h>

/**
 * NVIC Registers Base Address
 * ARM Cortex-M33 TRM NVIC Register Summary
 **/
#define EM_NVIC_BASE_ADDRESS 0xE000E000

/**
 * NVIC Registers
 * ARM Cortex-M33 TRM NVIC Register Summary
 **/
#define EM_NVIC_ICTR 0x00004
#define EM_NVIC_ICTR_NS 0x20004
#define EM_NVIC_ISER 0x00100

/**
 * NVIC Modifiers
 **/
#define EM_NVIC_ISER_STRIDE 0x4

/**
 * SCB Registers Base Address
 * ARM Cortex-M33 TRM System Control Register Summary
 **/
#define EM_SCB_BASE_ADDRESS 0xE000ED00

/**
 * SCB Registers
 * ARM Cortex-M33 TRM SCB Register Summary
 **/
#define EM_SCB_CPUID 0x00
#define EM_SCB_ICSR 0x04
#define EM_SCB_VTOR 0x08

/**
 * NVIC IRQs
 **/
#define EM_TIMER0_ALARM0 0
#define EM_TIMER0_ALARM1 1
#define EM_TIMER0_ALARM2 2
#define EM_TIMER0_ALARM3 3
#define EM_TIMER1_ALARM0 4
#define EM_TIMER1_ALARM1 5
#define EM_TIMER1_ALARM2 6
#define EM_TIMER1_ALARM3 7

typedef void (*em_irq_handler_t)(void);

void em_nvic_enable(uint8_t irq);

void em_nvic_set_handler(uint8_t irq, em_irq_handler_t handler);

#endif
