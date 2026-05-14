// Various memory allocators
#include <stddef.h>
#include <stdint.h>

#include "emblib/config.h"
#include "emblib/error.h"
#include "emblib/mem.h"

static em_block_t pool[EMBLIB_MEM_BLOCK_COUNT] __attribute__((aligned(sizeof(em_block_t))));
static em_block_t *free_list = NULL;

em_err_t em_static_init(void) {
  // Initialize the block memory with internal linked list
  for (unsigned block_index = 0; block_index < EMBLIB_MEM_BLOCK_COUNT; block_index++) {
    em_block_t *block_ptr = (em_block_t *)&pool[block_index];

    block_ptr->next = (block_index == EMBLIB_MEM_BLOCK_COUNT - 1) ? NULL : (em_block_t *)&pool[(block_index + 1)];
  }

  free_list = (em_block_t *)pool;
  return EM_OK;
}

em_err_t em_static_alloc(void **ptr) {
  if (free_list == NULL) {
    return EM_ERR_NO_MEM;
  }

  em_block_t *new_mem = free_list;
  free_list = free_list->next;

  *ptr = (void *)new_mem;
  return EM_OK;
}

em_err_t em_static_free(void *ptr) {
  em_block_t *free_mem = (em_block_t *)ptr;

  if (free_mem < pool || free_mem >= &pool[EMBLIB_MEM_BLOCK_COUNT]) {
    return EM_ERR_OOB;
  }

  // Confirm alignment of memory being free'd
  if ((uintptr_t)free_mem % sizeof(em_block_t) != 0) {
    return EM_ERR_UNALIGN;
  }

  // Check if this block will become the new front of the list
  if (free_list == NULL || free_mem < free_list) {

    free_mem->next = free_list;
    free_list = free_mem;

    return EM_OK;
  }

  // Search the blocks for the insertion point of our new free memory
  em_block_t *block_iter = free_list;
  em_block_t *prev_iter = NULL;
  while (block_iter != NULL && free_mem > block_iter) {
    prev_iter = block_iter;
    block_iter = block_iter->next;
  }

  // Check if this memory to be freed is already in the free list
  if (block_iter == free_mem) {
    return EM_ERR_INVALID;
  }

  // Insert our block back into the free mem list
  prev_iter->next = free_mem;
  free_mem->next = block_iter;

  return EM_OK;
}
