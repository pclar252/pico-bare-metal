#ifndef EMBLIB_PAD_H
#define EMBLIB_PAD_H

#include <stdint.h>

/**
 * Pad Control Bank 0 Base Address
 * RP2350 9.11.3
 */
#define EM_PADS_BANK0_BASE 0x40038000

/**
 * Pad Control Registers
 * RP2350 9.11.3
 **/
#define EM_PADS_BANK0_GPIO_BASE 0x04

/**
 * Pad Register Modifiers
 * RP2350 9.11.3
 **/
#define EM_PADS_GPIO_STRIDE 0x04
#define EM_PADS_GPIO_IE (1u << 6)
#define EM_PADS_GPIO_ISO (1u << 8)

void em_pads_set_ie(uint8_t pin);

void em_pads_clr_iso(uint8_t pin);

#endif
