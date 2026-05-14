#include "emblib/config.h"
#include "emblib/error.h"
#include "emblib/mem.h"
#include "unity_internals.h"

#include <stdint.h>
#include <unity.h>

// Basic alloc
void test_mem_basic_alloc(void) {
  unsigned *ptr = NULL;
  // Alloc
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&ptr));
  TEST_ASSERT_NOT_NULL(ptr);

  // Free
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(ptr));
}

// Multiple allocs are distinct
void test_mem_multi_alloc(void) {
  unsigned *p1 = NULL, *p2 = NULL, *p3 = NULL;

  // Alloc
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&p1));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&p2));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&p3));

  TEST_ASSERT_NOT_NULL(p1);
  TEST_ASSERT_NOT_NULL(p2);
  TEST_ASSERT_NOT_NULL(p3);

  // Confirm each alloc is unique
  TEST_ASSERT_NOT_EQUAL(p1, p2);
  TEST_ASSERT_NOT_EQUAL(p1, p3);
  TEST_ASSERT_NOT_EQUAL(p2, p3);

  // Free
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(p1));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(p2));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(p3));
}

// Exhaust the pool
void test_mem_full_alloc(void) {
  unsigned *ptr_pool[EMBLIB_MEM_BLOCK_COUNT];

  // Allocate all the blocks in the pool
  for (unsigned i = 0; i < EMBLIB_MEM_BLOCK_COUNT; i++) {
    TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void *)&ptr_pool[i]));
    TEST_ASSERT_NOT_NULL(ptr_pool[i]);
  }

  // Attempt to allocate after the pool should be empty
  unsigned *full_ptr = NULL;
  TEST_ASSERT_EQUAL_INT(EM_ERR_NO_MEM, em_static_alloc((void *)&full_ptr));
  TEST_ASSERT_NULL(full_ptr);
}

// Free and re-alloc
void test_mem_free_realloc(void) {
  unsigned *ptr = NULL;
  // Alloc
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&ptr));
  TEST_ASSERT_NOT_NULL(ptr);

  unsigned *old_ptr = ptr;

  // Free
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(ptr));
  ptr = NULL;

  // Re-alloc
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&ptr));
  TEST_ASSERT_NOT_NULL(ptr);

  // Should re-allocate the same block that was free'd
  TEST_ASSERT_EQUAL_PTR(old_ptr, ptr);
}

// OOB Free
void test_mem_oob_free(void) {
  unsigned local = 0;
  TEST_ASSERT_EQUAL_INT(EM_ERR_OOB, em_static_free((void *)&local));
}

// Free ordering
void test_mem_free_ordering(void) {
  unsigned *p1 = NULL, *p2 = NULL, *p3 = NULL;
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&p1));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&p2));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&p3));

  // Free middle, first, last
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(p2));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(p1));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(p3));

  unsigned *r1 = NULL, *r2 = NULL, *r3 = NULL;
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&r1));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&r2));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&r3));

  TEST_ASSERT_NOT_NULL(r1);
  TEST_ASSERT_NOT_NULL(r2);
  TEST_ASSERT_NOT_NULL(r3);

  TEST_ASSERT_NOT_EQUAL(r1, r2);
  TEST_ASSERT_NOT_EQUAL(r1, r3);
  TEST_ASSERT_NOT_EQUAL(r2, r3);

  // Confirm the list reconstruction is correct
  TEST_ASSERT_EQUAL_PTR(p1, r1);
  TEST_ASSERT_EQUAL_PTR(p2, r2);
  TEST_ASSERT_EQUAL_PTR(p3, r3);
}

// Double free - block at head of free list
void test_mem_double_free_head(void) {
  unsigned *ptr = NULL;

  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&ptr));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(ptr));
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_static_free(ptr));
}

// Double free - block in middle of free list
void test_mem_double_free_mid(void) {
  unsigned *p1 = NULL, *p2 = NULL, *p3 = NULL;
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&p1));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&p2));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&p3));

  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(p1));
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_free(p3));

  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_static_free(p3));
}

// Misaligned free
void test_mem_misaligned_free(void) {
  unsigned *ptr = NULL;
  TEST_ASSERT_EQUAL_INT(EM_OK, em_static_alloc((void **)&ptr));

  void *misaligned = (uint8_t *)ptr + 1;
  TEST_ASSERT_EQUAL_INT(EM_ERR_UNALIGN, em_static_free(misaligned));
}

void run_mem_tests(void) {
  RUN_TEST(test_mem_basic_alloc);
  RUN_TEST(test_mem_multi_alloc);
  RUN_TEST(test_mem_full_alloc);
  RUN_TEST(test_mem_free_realloc);
  RUN_TEST(test_mem_oob_free);
  RUN_TEST(test_mem_free_ordering);
  RUN_TEST(test_mem_double_free_head);
  RUN_TEST(test_mem_double_free_mid);
  RUN_TEST(test_mem_misaligned_free);
}
