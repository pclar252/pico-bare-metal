#ifndef EMBLIB_REG_H
#define EMBLIB_REG_H

#include <stdint.h>

#define EM_REG_ALIAS_RW  0x0000u
#define EM_REG_ALIAS_XOR 0x1000u
#define EM_REG_ALIAS_SET 0x2000u
#define EM_REG_ALIAS_CLR 0x3000u

static inline volatile uint32_t *add_alias(volatile uint32_t *addr, uint32_t offset) {
  uintptr_t raw_val = (uintptr_t)addr + offset;
  return (volatile uint32_t *)raw_val;
}

static inline void em_reg_write(volatile uint32_t *addr, uint32_t data) {
  volatile uint32_t *adjusted_addr = add_alias(addr, EM_REG_ALIAS_RW);
  *adjusted_addr = data;
}

static inline uint32_t em_reg_read(volatile uint32_t *addr) {
  volatile uint32_t *adjusted_addr = add_alias(addr, EM_REG_ALIAS_RW);
  return *adjusted_addr;
}

static inline void em_reg_xor(volatile uint32_t *addr, uint32_t mask) {
  volatile uint32_t *adjusted_addr = add_alias(addr, EM_REG_ALIAS_XOR);
  *adjusted_addr = mask;
}

static inline void em_reg_set(volatile uint32_t *addr, uint32_t mask) {
  volatile uint32_t *adjusted_addr = add_alias(addr, EM_REG_ALIAS_SET);
  *adjusted_addr = mask;
}

static inline void em_reg_clr(volatile uint32_t *addr, uint32_t mask) {
  volatile uint32_t *adjusted_addr = add_alias(addr, EM_REG_ALIAS_CLR);
  *adjusted_addr = mask;
}

#endif
