#ifndef EMBLIB_RING_H
#define EMBLIB_RING_H

#include <stddef.h>
#include <stdint.h>

#include "emblib/error.h"

typedef struct {
  uint8_t *_buf;
  size_t _capacity;
  size_t _head;
  size_t _tail;
  size_t _count;
} em_rb_t;

em_err_t em_rb_init(em_rb_t *rb, uint8_t *buf, size_t capacity);

em_err_t em_rb_write(em_rb_t *rb, const uint8_t *data, size_t len);

em_err_t em_rb_read(em_rb_t *rb, uint8_t *data, size_t len);

em_err_t em_rb_count(const em_rb_t *rb, size_t *out);

em_err_t em_rb_space(const em_rb_t *rb, size_t *out);

#endif /* EMBLIB_RING_H */
