#include "emblib/cs.h"

static uint32_t irq_enter(void *ctx) {
    (void)ctx;
    uint32_t primask;
    __asm__ volatile("mrs %0, PRIMASK" : "=r"(primask));
    __asm__ volatile("cpsid i" ::: "memory");
    return primask;
}

static void irq_exit(void *ctx, uint32_t saved) {
    (void)ctx;
    __asm__ volatile("msr PRIMASK, %0" ::"r"(saved) : "memory");
}

em_cs_t em_cs_irq = {
    .enter = irq_enter,
    .exit  = irq_exit,
    .ctx   = NULL,
};
