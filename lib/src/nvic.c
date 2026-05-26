#include <emblib/nvic.h>
#include <stdint.h>

void em_nvic_enable(uint8_t irq) {
  *(volatile uint32_t *)(EM_NVIC_BASE_ADDRESS + EM_NVIC_ISER + (irq / 32) * EM_NVIC_ISER_STRIDE) = (1u << (irq % 32));
  __asm__ volatile("dsb" ::: "memory");
  __asm__ volatile("isb" ::: "memory");
}

void em_nvic_set_handler(uint8_t irq, em_irq_handler_t handler) {
  uint32_t vtor_address = *(volatile uint32_t *)(EM_SCB_BASE_ADDRESS + EM_SCB_VTOR);
  volatile em_irq_handler_t *vt = (volatile em_irq_handler_t *)vtor_address;

  vt[16 + irq] = handler;
  __asm__ volatile("dsb" ::: "memory");
  __asm__ volatile("isb" ::: "memory");
}
