#include <emblib/reg.h>
#include <emblib/sio.h>
#include <stdint.h>

static inline void sio_write(uint32_t offset, uint8_t pin) {
  volatile uint32_t *reg = (volatile uint32_t *)(EM_SIO_BASE + offset);
  em_reg_write(reg, (1u << pin));
}

void em_sio_gpio_oe_set(uint8_t pin) { sio_write(EM_SIO_GPIO_OE + EM_GPIO_MOD_SET, pin); }
void em_sio_gpio_oe_clr(uint8_t pin) { sio_write(EM_SIO_GPIO_OE + EM_GPIO_MOD_CLR, pin); }
void em_sio_gpio_oe_xor(uint8_t pin) { sio_write(EM_SIO_GPIO_OE + EM_GPIO_MOD_XOR, pin); }

void em_sio_gpio_out_set(uint8_t pin) { sio_write(EM_SIO_GPIO_OUT + EM_GPIO_MOD_SET, pin); }
void em_sio_gpio_out_clr(uint8_t pin) { sio_write(EM_SIO_GPIO_OUT + EM_GPIO_MOD_CLR, pin); }
void em_sio_gpio_out_xor(uint8_t pin) { sio_write(EM_SIO_GPIO_OUT + EM_GPIO_MOD_XOR, pin); }
