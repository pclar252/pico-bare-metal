#include "emblib/error.h"
#include "emblib/ring.h"

#include <unity.h>

void test_rb_init_valid(void) {
  em_rb_t rb;
  uint8_t buf[8];
  TEST_ASSERT_EQUAL_INT(EM_OK, em_rb_init(&rb, buf, sizeof(buf), NULL));
}

void test_rb_init_null_rb(void) {
  uint8_t buf[8];
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_init(NULL, buf, sizeof(buf), NULL));
}

void test_rb_init_null_buf(void) {
  em_rb_t rb;
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_init(&rb, NULL, 8, NULL));
}

void test_rb_init_zero_capacity(void) {
  em_rb_t rb;
  uint8_t buf[8];
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_init(&rb, buf, 0, NULL));
}

void test_rb_write_basic(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  uint8_t data[] = {1, 2, 3};
  TEST_ASSERT_EQUAL_INT(EM_OK, em_rb_write(&rb, data, sizeof(data)));

  size_t count;
  em_rb_count(&rb, &count);
  TEST_ASSERT_EQUAL_size_t(3, count);
}

void test_rb_write_null_rb(void) {
  uint8_t data[] = {1, 2, 3};
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_write(NULL, data, sizeof(data)));
}

void test_rb_write_null_data(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_write(&rb, NULL, 3));
}

void test_rb_write_overflow(void) {
  em_rb_t rb;
  uint8_t buf[4];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  uint8_t data[] = {1, 2, 3, 4, 5};
  TEST_ASSERT_EQUAL_INT(EM_ERR_NO_MEM, em_rb_write(&rb, data, sizeof(data)));
}

void test_rb_write_exact_capacity(void) {
  em_rb_t rb;
  uint8_t buf[4];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  uint8_t data[] = {1, 2, 3, 4};
  TEST_ASSERT_EQUAL_INT(EM_OK, em_rb_write(&rb, data, sizeof(data)));

  size_t space;
  em_rb_space(&rb, &space);
  TEST_ASSERT_EQUAL_size_t(0, space);
}

void test_rb_read_basic(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  uint8_t written[] = {10, 20, 30};
  em_rb_write(&rb, written, sizeof(written));

  uint8_t read[3] = {0};
  TEST_ASSERT_EQUAL_INT(EM_OK, em_rb_read(&rb, read, sizeof(read)));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(written, read, sizeof(written));
}

void test_rb_read_null_rb(void) {
  uint8_t data[3];
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_read(NULL, data, sizeof(data)));
}

void test_rb_read_null_data(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  uint8_t written[] = {1, 2, 3};
  em_rb_write(&rb, written, sizeof(written));

  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_read(&rb, NULL, 3));
}

void test_rb_read_empty(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  uint8_t data[3];
  TEST_ASSERT_EQUAL_INT(EM_ERR_OOB, em_rb_read(&rb, data, sizeof(data)));
}

void test_rb_read_underflow(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  uint8_t written[] = {1, 2};
  em_rb_write(&rb, written, sizeof(written));

  uint8_t data[5];
  TEST_ASSERT_EQUAL_INT(EM_ERR_OOB, em_rb_read(&rb, data, sizeof(data)));
}

void test_rb_count_null_rb(void) {
  size_t count;
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_count(NULL, &count));
}

void test_rb_count_null_out(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_count(&rb, NULL));
}

void test_rb_space_null_rb(void) {
  size_t space;
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_space(NULL, &space));
}

void test_rb_space_null_out(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);
  TEST_ASSERT_EQUAL_INT(EM_ERR_INVALID, em_rb_space(&rb, NULL));
}

void test_rb_space_decreases_after_write(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  size_t space;
  em_rb_space(&rb, &space);
  TEST_ASSERT_EQUAL_size_t(8, space);

  uint8_t data[] = {1, 2, 3};
  em_rb_write(&rb, data, sizeof(data));

  em_rb_space(&rb, &space);
  TEST_ASSERT_EQUAL_size_t(5, space);
}

void test_rb_count_increases_after_write(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  uint8_t data[] = {1, 2, 3};
  em_rb_write(&rb, data, sizeof(data));

  size_t count;
  em_rb_count(&rb, &count);
  TEST_ASSERT_EQUAL_size_t(3, count);

  em_rb_write(&rb, data, sizeof(data));
  em_rb_count(&rb, &count);
  TEST_ASSERT_EQUAL_size_t(6, count);
}

void test_rb_count_decreases_after_read(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  uint8_t data[] = {1, 2, 3, 4};
  em_rb_write(&rb, data, sizeof(data));

  uint8_t out[2];
  em_rb_read(&rb, out, sizeof(out));

  size_t count;
  em_rb_count(&rb, &count);
  TEST_ASSERT_EQUAL_size_t(2, count);
}

void test_rb_wrap_around(void) {
  em_rb_t rb;
  uint8_t buf[8];
  em_rb_init(&rb, buf, sizeof(buf), NULL);

  // Fill 6 of 8 bytes
  uint8_t first[] = {1, 2, 3, 4, 5, 6};
  em_rb_write(&rb, first, sizeof(first));

  // Drain 4, leaving {5, 6} at positions 4 and 5
  uint8_t discard[4];
  em_rb_read(&rb, discard, sizeof(discard));

  // Write 5 more — wraps from position 6 back around to 0, 1, 2
  uint8_t second[] = {7, 8, 9, 10, 11};
  TEST_ASSERT_EQUAL_INT(EM_OK, em_rb_write(&rb, second, sizeof(second)));

  // Read all 7 remaining bytes and verify order is preserved
  uint8_t result[7];
  TEST_ASSERT_EQUAL_INT(EM_OK, em_rb_read(&rb, result, sizeof(result)));

  uint8_t expected[] = {5, 6, 7, 8, 9, 10, 11};
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, result, sizeof(expected));
}

void run_ring_tests(void) {
  RUN_TEST(test_rb_init_valid);
  RUN_TEST(test_rb_init_null_rb);
  RUN_TEST(test_rb_init_null_buf);
  RUN_TEST(test_rb_init_zero_capacity);

  RUN_TEST(test_rb_write_basic);
  RUN_TEST(test_rb_write_null_rb);
  RUN_TEST(test_rb_write_null_data);
  RUN_TEST(test_rb_write_overflow);
  RUN_TEST(test_rb_write_exact_capacity);

  RUN_TEST(test_rb_read_basic);
  RUN_TEST(test_rb_read_null_rb);
  RUN_TEST(test_rb_read_null_data);
  RUN_TEST(test_rb_read_empty);
  RUN_TEST(test_rb_read_underflow);

  RUN_TEST(test_rb_count_null_rb);
  RUN_TEST(test_rb_count_null_out);
  RUN_TEST(test_rb_space_null_rb);
  RUN_TEST(test_rb_space_null_out);
  RUN_TEST(test_rb_space_decreases_after_write);
  RUN_TEST(test_rb_count_increases_after_write);
  RUN_TEST(test_rb_count_decreases_after_read);

  RUN_TEST(test_rb_wrap_around);
}
