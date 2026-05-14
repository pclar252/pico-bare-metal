#ifndef EMBLIB_MEM_H
#define EMBLIB_MEM_H

#include <stdint.h>

#include "emblib/config.h"
#include "emblib/error.h"

typedef union em_block {
  union em_block *next;
  uint8_t data[EMBLIB_MEM_BLOCK_SIZE];
} em_block_t;

em_err_t em_static_init(void);

em_err_t em_static_alloc(void **ptr);

em_err_t em_static_free(void *ptr);

#endif /* EMBLIB_MEM_H */
