#ifndef EMBLIB_TIMER_H
#define EMBLIB_TIMER_H

/**
 * TICKS Base Address
 * RP2350 8.5.2
 **/
#include <stdint.h>
#define EM_TICKS_BASE 0x40108000

/**
 * TICKS TIMER0 Registers
 * RP2350 8.5.2
 **/
#define EM_TICKS_TIMER0_CTRL 0x18
#define EM_TICKS_TIMER0_CYCLES 0x1c
#define EM_TICKS_TIMER0_COUNT 0x20

/**
 * TIMER0 Base Address
 * RP2350 12.8.5
 **/
#define EM_TIMER0_BASE 0x400b0000

/**
 * TIMER0 Registers
 * RP2350 12.8.5
 **/
#define EM_TIMER0_TIMEHW 0x00
#define EM_TIMER0_TIMELW 0x04
#define EM_TIMER0_TIMEHR 0x08
#define EM_TIMER0_TIMELR 0x0c
#define EM_TIMER0_ALARM_BASE 0x10
#define EM_TIMER0_ARMED 0x20
#define EM_TIMER0_TIMERAWH 0x24
#define EM_TIMER0_TIMERAWL 0x28
#define EM_TIMER0_DBGPAUSE 0x2c
#define EM_TIMER0_PAUSE 0x30
#define EM_TIMER0_LOCKED 0x34
#define EM_TIMER0_SOURCE 0x38
#define EM_TIMER0_INTR 0x3c
#define EM_TIMER0_INTE 0x40
#define EM_TIMER0_INTF 0x44
#define EM_TIMER0_INTS 0x48

/**
 * TIMER0 Modifiers
 **/
#define EM_TIMER_ALARM_STRIDE 0x04

void em_timer0_intr_clr(uint8_t alarm);

void em_timer0_inte_set(uint8_t alarm);

void em_timer0_schedule_abs(uint8_t alarm, uint32_t time);
void em_timer0_schedule_rel(uint8_t alarm, uint32_t delta);

#endif
