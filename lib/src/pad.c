#include <emblib/pad.h>
#include <emblib/reg.h>

static inline volatile uint32_t *pad_reg(uint8_t pin) {
  return (volatile uint32_t *)(EM_PADS_BANK0_BASE
      + EM_PADS_BANK0_GPIO_BASE
      + pin * EM_PADS_GPIO_STRIDE);
}

void em_pads_set_ie(uint8_t pin)  { em_reg_set(pad_reg(pin), EM_PADS_GPIO_IE);  }
void em_pads_clr_iso(uint8_t pin) { em_reg_clr(pad_reg(pin), EM_PADS_GPIO_ISO); }
