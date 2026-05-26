#include <emblib/gpio.h>

#include <emblib/io_bank.h>
#include <emblib/pad.h>
#include <emblib/sio.h>

void em_gpio_init(uint8_t pin, em_func_t func) {
  // Enable the input buffer on the electrical pad
  em_pads_set_ie(pin);

  // Put SIO in a known safe state before routing the pin to it
  switch (func) {
  case EM_SIO_0:
    em_sio_gpio_oe_clr(pin);
    em_sio_gpio_out_clr(pin);
    break;
  default:
    break;
  }

  // Set the IO mux to connect this pin to the chosen peripheral
  em_io_bank0_set_func(pin, func);

  // Release pad isolation — pin is now live in a known state
  em_pads_clr_iso(pin);
}

void em_gpio_set_dir(uint8_t pin, uint8_t dir) {
  if (dir == EM_GPIO_OUT) {
    em_sio_gpio_oe_set(pin);
  } else {
    em_sio_gpio_oe_clr(pin);
  }
}
