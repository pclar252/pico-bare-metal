#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_mem(void);

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_mem);
  return UNITY_END();
}
