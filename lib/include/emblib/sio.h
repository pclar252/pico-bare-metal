#ifndef EMBLIB_SIO_H
#define EMBLIB_SIO_H

#include <stdint.h>

/**
 * SIO Peripheral Base Address
 * RP2350 2.2.6
 **/
#define EM_SIO_BASE 0xD0000000
#define EM_SIO_NONSEC_BASE 0xD0020000

/**
 * SIO Register Offsets
 * RP2350 3.1.11
 **/
#define EM_SIO_GPIO_OUT 0x010
#define EM_SIO_GPIO_OE  0x030

// Set of a modifiers to apply to base GPIO registers
#define EM_GPIO_MOD_SET 0x008
#define EM_GPIO_MOD_CLR 0x010
#define EM_GPIO_MOD_XOR 0x018

void em_sio_gpio_oe_set(uint8_t pin);
void em_sio_gpio_oe_clr(uint8_t pin);
void em_sio_gpio_oe_xor(uint8_t pin);

void em_sio_gpio_out_set(uint8_t pin);
void em_sio_gpio_out_clr(uint8_t pin);
void em_sio_gpio_out_xor(uint8_t pin);

#endif
