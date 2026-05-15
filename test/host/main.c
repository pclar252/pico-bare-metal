#include <unity.h>

#include "emblib/mem.h"

#include <test_mem.h>
#include <test_ring.h>

void setUp(void) { em_static_init(); }
void tearDown(void) {}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(run_mem_tests);
  RUN_TEST(run_ring_tests);
  return UNITY_END();
}
