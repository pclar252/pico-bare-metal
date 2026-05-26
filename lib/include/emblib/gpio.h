#ifndef EMBLIB_GPIO_H
#define EMBLIB_GPIO_H

#include <emblib/io_bank.h>

#include <stdint.h>

#define EM_GPIO_IN  0u
#define EM_GPIO_OUT 1u

void em_gpio_init(uint8_t pin, em_func_t func);

void em_gpio_set_dir(uint8_t pin, uint8_t dir);

#endif
