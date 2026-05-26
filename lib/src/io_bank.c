#include <emblib/io_bank.h>
#include <emblib/reg.h>

static inline volatile uint32_t *io_bank0_ctrl_reg(uint8_t pin) {
  return (volatile uint32_t *)(EM_IO_BANK0_BASE
      + EM_IO_BANK0_CTRL
      + EM_IO_BANK0_CTRL_STRIDE * pin);
}

void em_io_bank0_set_func(uint8_t pin, em_func_t func) {
  em_reg_write(io_bank0_ctrl_reg(pin), func);
}
