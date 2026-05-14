// Ring buffer
#include "emblib/ring.h"
#include "emblib/error.h"
#include <stddef.h>

em_err_t em_rb_init(em_rb_t *rb, uint8_t *buf, size_t capacity) {
  if (rb == NULL || buf == NULL || capacity == 0) {
    return EM_ERR_INVALID;
  }

  rb->_buf = buf;
  rb->_capacity = capacity;
  rb->_head = 0;
  rb->_tail = 0;
  rb->_count = 0;

  return EM_OK;
}

em_err_t em_rb_write(em_rb_t *rb, const uint8_t *data, size_t len) {
  if (rb == NULL || rb->_buf == NULL || data == NULL) {
    return EM_ERR_INVALID;
  }

  if ((len + rb->_count) > rb->_capacity) {
    return EM_ERR_NO_MEM;
  }

  for (size_t i = 0; i < len; i++) {
    size_t insert_index = (rb->_tail + i) % rb->_capacity;
    rb->_buf[insert_index] = data[i];
  }

  rb->_count += len;
  rb->_tail = (rb->_tail + len) % rb->_capacity;

  return EM_OK;
}

em_err_t em_rb_read(em_rb_t *rb, uint8_t *data, size_t len) {
  if (rb == NULL || rb->_buf == NULL || data == NULL) {
    return EM_ERR_INVALID;
  }

  if (len > rb->_count) {
    return EM_ERR_OOB;
  }

  for (size_t i = 0; i < len; i++) {
    size_t read_index = (rb->_head + i) % rb->_capacity;
    data[i] = rb->_buf[read_index];
  }

  rb->_count -= len;
  rb->_head = (rb->_head + len) % rb->_capacity;

  return EM_OK;
}

em_err_t em_rb_count(const em_rb_t *rb, size_t *out) {
  if (rb == NULL || out == NULL) {
    return EM_ERR_INVALID;
  }

  *out = rb->_count;

  return EM_OK;
}

em_err_t em_rb_space(const em_rb_t *rb, size_t *out) {
  if (rb == NULL || out == NULL) {
    return EM_ERR_INVALID;
  }

  *out = rb->_capacity - rb->_count;

  return EM_OK;
}
