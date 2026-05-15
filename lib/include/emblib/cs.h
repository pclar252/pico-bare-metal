#ifndef EMBLIB_CS_H
#define EMBLIB_CS_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t (*enter)(void *ctx);
    void (*exit)(void *ctx, uint32_t saved);
    void *ctx;
} em_cs_t;

static inline uint32_t em_cs_enter(em_cs_t *cs) {
    if (cs == NULL) return 0;
    return cs->enter(cs->ctx);
}

static inline void em_cs_exit(em_cs_t *cs, uint32_t saved) {
    if (cs == NULL) return;
    cs->exit(cs->ctx, saved);
}

extern em_cs_t em_cs_irq;

#endif /* EMBLIB_CS_H */
