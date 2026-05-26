#ifndef EMBLIB_IO_BANK_H
#define EMBLIB_IO_BANK_H

#include <stdint.h>

/**
 * IO_BANK0 Register Base Address
 * RP2350 9.11.1
 **/
#define EM_IO_BANK0_BASE 0x40028000

#define EM_IO_BANK0_STATUS 0x000
#define EM_IO_BANK0_CTRL 0x004

/**
 * IO_BANK0 Modifiers
 * RP2350 9.11.1
 **/
// The stride of the CTRL register is 0x008, meaning you can access any pins CTRL by BASE + CTRL + STRIDE * index
#define EM_IO_BANK0_CTRL_STRIDE 0x008

/**
 * IO_BANK0 FUNCSEL
 * RP2350 9.11.1
 **/
typedef enum {
  // EM_JTAG_TCK = 0x00,
  // EM_SPIO_RX = 0x01,
  // EM_UART0_TX = 0x02,
  // EM_I2C0_SDA = 0x03,
  // EM_PWM_A_0 = 0x04,
  EM_SIO_0 = 0x05,
  EM_PIO0_0 = 0x06,
  // EM_PIO1_0 = 0x07,
  // EM_PIO2_0 = 0x08,
  // EM_XIP_SS_N_1 = 0x09,
  // EM_USB_MUXING_OVERCURR_DETECT = 0x0A,
  EM_NULL = 0x1F,
} em_func_t;

void em_io_bank0_set_func(uint8_t pin, em_func_t func);

#endif
