#include <check.h>

#include "../s21_decimal.h"

START_TEST(add_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int = 0;
  s21_from_int_to_decimal(173789, &test_v_1);
  s21_from_int_to_decimal(47920, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 173789 + 47920);
}
END_TEST

START_TEST(add_2) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(78403, &test_v_1);
  s21_from_int_to_decimal(-3403, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 78403 + (-3403));
}
END_TEST

START_TEST(add_3) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(-90432, &test_v_1);
  s21_from_int_to_decimal(674833, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -90432 + 674833);
}
END_TEST

START_TEST(add_4) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(-90432, &test_v_1);
  s21_from_int_to_decimal(-3403, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, (-90432) + (-3403));
}
END_TEST

START_TEST(add_5) {
  s21_decimal test_v_1 = {{3784, 145, 11, 0}};
  s21_decimal test_v_2 = {{8594, 25, 894, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 3784 + 8594);
  ck_assert_uint_eq(result_dec.bits[1], 145 + 25);
  ck_assert_uint_eq(result_dec.bits[2], 11 + 894);
}
END_TEST

START_TEST(add_6) {
  s21_decimal test_v_1 = {{S21_UINT_MAX, 10, 10, 0}};
  s21_decimal test_v_2 = {{1, 2, 20, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 0);
  ck_assert_uint_eq(result_dec.bits[1], 13);
  ck_assert_uint_eq(result_dec.bits[2], 30);
}
END_TEST

START_TEST(add_7) {
  s21_decimal test_v_1 = {{S21_UINT_MAX, S21_UINT_MAX, S21_UINT_MAX, 0}};
  s21_decimal test_v_2 = {{1, 1, 1, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result = s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(add_8) {
  s21_decimal test_v_1 = {{S21_UINT_MAX, S21_UINT_MAX, S21_UINT_MAX, 0}};
  s21_decimal test_v_2 = {{1, 1, 1, 0}};
  s21_set_bits(&test_v_1, 127, 1);
  s21_set_bits(&test_v_2, 127, 1);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result = s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(add_9) {
  s21_decimal test_v_1 = {{S21_UINT_MAX, S21_UINT_MAX, S21_UINT_MAX, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294967295);
  ck_assert_uint_eq(result_dec.bits[1], 4294967295);
  ck_assert_uint_eq(result_dec.bits[2], 4294967295);
  ck_assert_uint_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(add_10) {
  s21_decimal src1 = {{0}}, src2 = {{0}}, result = {{0}};
  int a = -1234;
  float b = 1.234;
  float res_origin = -1232.766;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_11) {
  s21_decimal src1 = {{0}}, src2 = {{0}}, result = {{0}};
  int a = -1234;
  float b = -1.234;
  float res_origin = -1235.234;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_12) {
  s21_decimal src1 = {{0}}, src2 = {{0}}, result = {{0}};
  float a = -1234;
  float b = -221.23401;
  float res_origin = -1455.234;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_13) {
  s21_decimal src1 = {{0}}, src2 = {{0}}, result = {{0}};
  float a = -9403;
  float b = 0.00234;
  float res_origin = -9402.9976600;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_14) {
  s21_decimal src1 = {{0}}, src2 = {{0}}, result = {{0}};
  float a = -940.3;
  float b = 0.234;
  float res_origin = -940.0660000;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_15) {
  s21_decimal src1 = {{0}}, src2 = {{0}}, result = {{0}};
  float a = -0.940301;
  float b = 22.023401;
  float res_origin = 21.0831;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_16) {
  s21_decimal src1 = {{0}}, src2 = {{0}}, result = {{0}};
  float a = -0.9403;
  float b = -112.0234;
  float res_origin = -112.9637;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_17) {
  s21_decimal src1 = {{0}}, src2 = {{0}}, result = {{0}};
  float a = -0.94e03;
  float b = -112.0234;
  float res_origin = -1052.0234;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_18) {
  s21_decimal src1 = {{0}}, src2 = {{0}}, result = {{0}};
  float a = -0.94e03;
  float b = -112.0e2;
  float res_origin = -12140;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_19) {
  s21_decimal test_v_1 = {{S21_UINT_MAX, S21_UINT_MAX, S21_UINT_MAX - 5, 0}};
  s21_decimal test_v_2 = {{100, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 99);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(add_20) {
  s21_decimal test_v_1 = {
      {S21_UINT_MAX, S21_UINT_MAX, S21_UINT_MAX - 5, 131072}};
  s21_decimal test_v_2 = {{0, 1, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 4294967295);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(add_21) {
  s21_decimal test_v_1 = {
      {S21_UINT_MAX, S21_UINT_MAX, S21_UINT_MAX - 5, 131072}};
  s21_decimal test_v_2 = {{5, 0, 1, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 4);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], S21_UINT_MAX - 3);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(add_22) {
  s21_decimal test_v_1 = {{428, 0, 0, 0}};
  s21_decimal test_v_2 = {{165, 0, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 42965);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 0);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(sub_1) {
  s21_decimal src1 = {{10000, 0, 0, 0}};
  s21_decimal src2 = {{500, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res_our;
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_int(result, &res_our);
  ck_assert_int_eq(res_our, 9500);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal src1 = {{9403, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float b = 202.098;
  float res_our;
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, 9200.902);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -9403;
  float b = 202.098;
  float res_origin = a - b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0;
  float b = 202.0098421232;
  float res_origin = 9200.9901578768;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(sub_5) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -9403.000;
  float b = 202.0098421232;
  float res_origin = -9605.0098421232;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(sub_6) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -9403.0e2;
  int b = -202;
  float res_origin = a - b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(sub_7) {
  s21_decimal test_v_1 = {{1, 10, 0, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4);
  ck_assert_uint_eq(result_dec.bits[2], 0);
}
END_TEST

START_TEST(sub_8) {
  s21_decimal test_v_1 = {{1, 4, 5, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967294);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(sub_9) {
  s21_decimal test_v_1 = {0}, test_v_2 = {0};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  test_v_1.bits[0] = 2834956;
  test_v_2.bits[0] = 3834956;
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 1000000);
}
END_TEST

START_TEST(sub_10) {
  s21_decimal test_v_1 = {0}, test_v_2 = {0};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  test_v_1.bits[0] = 2834956;
  s21_set_sign(&test_v_1, 1);
  s21_set_sign(&test_v_2, 1);
  test_v_2.bits[0] = 3834956;
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 1000000);
}
END_TEST

START_TEST(sub_11) {
  s21_decimal test_v_1 = {{1, 0, 5, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967290);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(sub_12) {
  s21_decimal test_v_1 = {{1, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 0}};
  s21_set_sign(&test_v_2, 1);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 5001);
  ck_assert_uint_eq(result_dec.bits[1], 0);
  ck_assert_uint_eq(result_dec.bits[2], 0);
  ck_assert_uint_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(mul_1) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 189940600;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_2) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0;
  float b = 9403.0;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 88416409;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_3) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403;
  float b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 1899406;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_4) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -65536;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_5) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 32768;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1073741824;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_6) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float res_our_dec = 0.0;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_int_eq(src1.bits[0], result.bits[0]);
  ck_assert_int_eq(src1.bits[1], result.bits[1]);
  ck_assert_int_eq(src1.bits[2], result.bits[2]);
}
END_TEST

START_TEST(mul_7) {
  s21_decimal src1 = {{S21_UINT_MAX, S21_UINT_MAX, S21_UINT_MAX, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(mul_8) {
  s21_decimal src1 = {{S21_UINT_MAX, S21_UINT_MAX, S21_UINT_MAX, 2147483648}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  float n1 = -5.6e-15;
  float n2 = 1.5e-15;
  s21_from_float_to_decimal(n1, &val1);
  s21_from_float_to_decimal(n2, &val2);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{10000, 0, 0, 131072}};
  s21_decimal val2 = {{100000, 0, 0, 131072}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(val1, val2, &res);
  ck_assert_int_eq(res.bits[0], 1000000000);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(div_1) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_2) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_div(src1, src2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(div_3) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(div_4) {
  s21_decimal src1 = {{1000, 0, 0, 65536}};  // 65536
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 500);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 65536);
}
END_TEST

START_TEST(div_5) {
  s21_decimal src1 = {{1000, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_6) {
  s21_decimal src1 = {{1000, 0, 0, 131072}};
  s21_decimal src2 = {{50, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 65536);
}
END_TEST

START_TEST(is_less_1) {
  s21_decimal test_v_1 = {{10, 0, 0, 0}};
  s21_decimal test_v_2 = {{15, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal test_v_1 = {{6739, 0, 0, 0}};
  s21_decimal test_v_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal test_v_1 = {{19993, 0, 0, 0}};
  s21_decimal test_v_2 = {{6739, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal test_v_1 = {{19993, 0, 0, 0}};
  s21_decimal test_v_2 = {{6739, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal test_v_1 = {{19993, 0, 0, 0}};
  s21_decimal test_v_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal test_v_1 = {{19993, 0, 0, 0}};
  s21_decimal test_v_2 = {{19993, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal test_v_1 = {{0, 1, 0, 0}};
  s21_decimal test_v_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal test_v_1 = {{19993, 1, 0, 2147483648}};
  s21_decimal test_v_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_less_or_equal_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_less_or_equal_5) {
  s21_decimal test_v_1 = {{0, 1, 0, 0}};
  s21_decimal test_v_2 = {{0, 1, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_greater_1) {
  s21_decimal dst1 = {{0}}, dst2 = {{0}};
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(is_greater_2) {
  s21_decimal dst1 = {{0}}, dst2 = {{0}};
  s21_from_float_to_decimal(-1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 1);
}
END_TEST

START_TEST(is_greater_3) {
  s21_decimal dst1 = {{0}}, dst2 = {{0}};
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(is_greater_4) {
  s21_decimal dst1 = {{0}}, dst2 = {{0}};
  s21_from_float_to_decimal(0.0, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);
}
END_TEST

START_TEST(is_greater_or_equal_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_equal_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal test_v_1 = {{5000, 1, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 2, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_not_equal_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(is_not_equal_2) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_not_equal_3) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_not_equal_4) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal test_v_1 = {{5000, 1, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 2, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(form_int_to_decimal_1) {
  s21_decimal result;
  s21_from_int_to_decimal(0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(form_int_to_decimal_2) {
  s21_decimal result;
  s21_from_int_to_decimal(-128, &result);
  ck_assert_int_eq(result.bits[0], 128);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(form_int_to_decimal_3) {
  s21_decimal result;
  s21_from_int_to_decimal(5000, &result);
  ck_assert_int_eq(result.bits[0], 5000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(form_int_to_decimal_4) {
  s21_decimal result;
  s21_from_int_to_decimal(-2147483648, &result);
  ck_assert_int_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(form_int_to_decimal_5) {
  s21_decimal result;
  s21_from_int_to_decimal(2147483647, &result);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(form_float_to_decimal_1) {
  s21_decimal result;
  s21_from_float_to_decimal(127.1234, &result);
  ck_assert_int_eq(result.bits[0], 1271234);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 262144);
}
END_TEST

START_TEST(form_float_to_decimal_2) {
  s21_decimal result;
  s21_from_float_to_decimal(22.14836E+03, &result);
  ck_assert_int_eq(result.bits[0], 2214836);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 131072);
}
END_TEST

START_TEST(form_float_to_decimal_4) {
  s21_decimal result;
  s21_from_float_to_decimal(-333.2222, &result);
  ck_assert_int_eq(result.bits[0], 3332222);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147745792);
}
END_TEST

START_TEST(decimal_to_int_2) {
  int number = 0;
  s21_decimal src = {{0, 0, 0, 0}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
}
END_TEST

START_TEST(decimal_to_int_3) {
  int number = 0;
  s21_decimal src = {{5000, 0, 0, 2147483648}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -5000);
}
END_TEST

START_TEST(decimal_to_int_4) {
  int number = 0;
  s21_decimal src = {{2147483648, 0, 0, 2147483648}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &number), 0);
}
END_TEST

START_TEST(decimal_to_float_1) {
  float number = 0.0;
  s21_decimal src = {{18122, 0, 0, 2147680256}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
}
END_TEST

START_TEST(decimal_to_float_2) {
  float number = 0.0;
  s21_decimal src = {{1812, 0, 0, 2147483648}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
}
END_TEST

START_TEST(floor_1) {
  s21_decimal v_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal v_1 = {{679988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal v_1 = {{679988, 0, 0, 2147745796}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 68);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(floor_4) {
  s21_decimal v_1 = {{2555, 0, 0, 0}};
  s21_set_scale(&v_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 25);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round_01) {
  // -98.78798789312
  s21_decimal d1 = {
      {0b00010110010010101110101011000000, 0b00000000000000000000100011111100,
       0b00000000000000000000000000000000, 0b10000000000010110000000000000000}};
  s21_decimal d2 = {{0}};
  // -99
  s21_decimal res = {
      {0b00000000000000000000000001100011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};

  s21_round(d1, &d2);
  ck_assert_int_eq(d2.bits[3], res.bits[3]);
  ck_assert_int_eq(d2.bits[2], res.bits[2]);
  ck_assert_int_eq(d2.bits[1], res.bits[1]);
  ck_assert_int_eq(d2.bits[0], res.bits[0]);
}
END_TEST

START_TEST(round_02) {
  // 999999999999999999911.3
  s21_decimal d1 = {
      {0b10110010001111111111110010001001, 0b00011001111000001100100110111010,
       0b00000000000000000000001000011110, 0b00000000000000010000000000000000}};
  s21_decimal d2 = {{0}};
  // 999999999999999999911
  s21_decimal res = {
      {0b11011110100111111111111110100111, 0b00110101110010011010110111000101,
       0b00000000000000000000000000110110, 0b00000000000000000000000000000000}};

  s21_round(d1, &d2);
  ck_assert_int_eq(d2.bits[3], res.bits[3]);
  ck_assert_int_eq(d2.bits[2], res.bits[2]);
  ck_assert_int_eq(d2.bits[1], res.bits[1]);
  ck_assert_int_eq(d2.bits[0], res.bits[0]);
}
END_TEST

START_TEST(round_03) {
  // -545454512454545.35265454545645
  s21_decimal d1 = {
      {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
  s21_decimal d2 = {{0}};
  // -545454512454545
  s21_decimal res = {
      {0b10000110011101001011101110010001, 0b00000000000000011111000000010110,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};

  s21_round(d1, &d2);
  ck_assert_int_eq(d2.bits[3], res.bits[3]);
  ck_assert_int_eq(d2.bits[2], res.bits[2]);
  ck_assert_int_eq(d2.bits[1], res.bits[1]);
  ck_assert_int_eq(d2.bits[0], res.bits[0]);
}
END_TEST

START_TEST(round_04) {
  // -364748.110
  s21_decimal d1 = {
      {0b00010101101111011001110101001110, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000110000000000000000}};
  s21_decimal d2 = {{0}};
  // -364748
  s21_decimal res = {
      {0b00000000000001011001000011001100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};

  s21_round(d1, &d2);
  ck_assert_int_eq(d2.bits[3], res.bits[3]);
  ck_assert_int_eq(d2.bits[2], res.bits[2]);
  ck_assert_int_eq(d2.bits[1], res.bits[1]);
  ck_assert_int_eq(d2.bits[0], res.bits[0]);
}
END_TEST

START_TEST(round_05) {
  // 7961327845421.879754123131254
  s21_decimal d1 = {
      {0b01001110111001000011100101110110, 0b01001011001101011010000111011001,
       0b00011001101110010111010010111111, 0b00000000000011110000000000000000}};
  s21_decimal d2 = {{0}};
  // 7961327845422
  s21_decimal res = {
      {0b10100100000111100100000000101110, 0b00000000000000000000011100111101,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_round(d1, &d2);
  ck_assert_int_eq(d2.bits[3], res.bits[3]);
  ck_assert_int_eq(d2.bits[2], res.bits[2]);
  ck_assert_int_eq(d2.bits[1], res.bits[1]);
  ck_assert_int_eq(d2.bits[0], res.bits[0]);
}
END_TEST

START_TEST(round_06) {
  // 12345677.987654345678987654346
  s21_decimal d1 = {
      {0b10010001000010101111010011001010, 0b11000000010001011101010111110010,
       0b00100111111001000001101100000000, 0b00000000000101010000000000000000}};
  s21_decimal d2 = {{0}};
  // 12345678
  s21_decimal res = {
      {0b00000000101111000110000101001110, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_round(d1, &d2);
  ck_assert_int_eq(d2.bits[3], res.bits[3]);
  ck_assert_int_eq(d2.bits[2], res.bits[2]);
  ck_assert_int_eq(d2.bits[1], res.bits[1]);
  ck_assert_int_eq(d2.bits[0], res.bits[0]);
}
END_TEST

START_TEST(round_07) {
  // -12345677.987654345678987654346
  s21_decimal d1 = {
      {0b10010001000010101111010011001010, 0b11000000010001011101010111110010,
       0b00100111111001000001101100000000, 0b10000000000101010000000000000000}};
  s21_decimal d2 = {{0}};
  // -12345678
  s21_decimal res = {
      {0b00000000101111000110000101001110, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};

  s21_round(d1, &d2);
  ck_assert_int_eq(d2.bits[3], res.bits[3]);
  ck_assert_int_eq(d2.bits[2], res.bits[2]);
  ck_assert_int_eq(d2.bits[1], res.bits[1]);
  ck_assert_int_eq(d2.bits[0], res.bits[0]);
}
END_TEST

START_TEST(round_08) {
  // 87654323456.9876545678987653
  s21_decimal d1 = {
      {0b00010001110011011101000110000101, 0b11110101101111000110111111000000,
       0b00000010110101010000111100111111, 0b00000000000100000000000000000000}};
  s21_decimal d2 = {{0}};
  // 87654323457
  s21_decimal res = {
      {0b01101000100110101101010100000001, 0b00000000000000000000000000010100,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_round(d1, &d2);
  ck_assert_int_eq(d2.bits[3], res.bits[3]);
  ck_assert_int_eq(d2.bits[2], res.bits[2]);
  ck_assert_int_eq(d2.bits[1], res.bits[1]);
  ck_assert_int_eq(d2.bits[0], res.bits[0]);
}
END_TEST

START_TEST(round_09) {
  // 336565445454313.859865545
  s21_decimal d1 = {
      {0b00111110111111000101101111001001, 0b00111111110101011110000010001011,
       0b00000000000000000100011101000101, 0b00000000000010010000000000000000}};
  s21_decimal d2 = {{0}};
  // 336565445454314
  s21_decimal res = {
      {0b10111111110100011110100111101010, 0b00000000000000010011001000011010,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};

  s21_round(d1, &d2);
  ck_assert_int_eq(d2.bits[3], res.bits[3]);
  ck_assert_int_eq(d2.bits[2], res.bits[2]);
  ck_assert_int_eq(d2.bits[1], res.bits[1]);
  ck_assert_int_eq(d2.bits[0], res.bits[0]);
}
END_TEST

START_TEST(round_10) {
  // -15456451234534
  s21_decimal d1 = {
      {0b10111100010010010000101011100110, 0b00000000000000000000111000001110,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal d2 = {{0}};
  // -15456451234534
  s21_decimal res = {
      {0b10111100010010010000101011100110, 0b00000000000000000000111000001110,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};

  s21_round(d1, &d2);
  ck_assert_int_eq(d2.bits[3], res.bits[3]);
  ck_assert_int_eq(d2.bits[2], res.bits[2]);
  ck_assert_int_eq(d2.bits[1], res.bits[1]);
  ck_assert_int_eq(d2.bits[0], res.bits[0]);
}
END_TEST

START_TEST(negate_1) {
  s21_decimal v_1 = {{155, 1, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal v_1 = {{155, 1, 1, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal v_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal v_1 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(-2744406, &v_1);
  s21_truncate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 2744406);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

int main(void) {
  int flag = 0;
  Suite *s = suite_create("s21_decimal: ");
  SRunner *sr = srunner_create(s);
  TCase *tc = tcase_create("s21_decimal: ");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);
  tcase_add_test(tc, add_3);
  tcase_add_test(tc, add_4);
  tcase_add_test(tc, add_5);
  tcase_add_test(tc, add_6);
  tcase_add_test(tc, add_7);
  tcase_add_test(tc, add_8);
  tcase_add_test(tc, add_9);
  tcase_add_test(tc, add_10);
  tcase_add_test(tc, add_11);
  tcase_add_test(tc, add_12);
  tcase_add_test(tc, add_13);
  tcase_add_test(tc, add_14);
  tcase_add_test(tc, add_15);
  tcase_add_test(tc, add_16);
  tcase_add_test(tc, add_17);
  tcase_add_test(tc, add_18);
  tcase_add_test(tc, add_19);
  tcase_add_test(tc, add_20);
  tcase_add_test(tc, add_21);
  tcase_add_test(tc, add_22);
  tcase_add_test(tc, sub_1);
  tcase_add_test(tc, sub_2);
  tcase_add_test(tc, sub_3);
  tcase_add_test(tc, sub_4);
  tcase_add_test(tc, sub_5);
  tcase_add_test(tc, sub_6);
  tcase_add_test(tc, sub_7);
  tcase_add_test(tc, sub_8);
  tcase_add_test(tc, sub_9);
  tcase_add_test(tc, sub_10);
  tcase_add_test(tc, sub_11);
  tcase_add_test(tc, sub_12);
  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, is_less_1);
  tcase_add_test(tc, is_less_2);
  tcase_add_test(tc, is_less_3);
  tcase_add_test(tc, is_less_4);
  tcase_add_test(tc, is_less_5);
  tcase_add_test(tc, is_less_6);
  tcase_add_test(tc, is_less_7);
  tcase_add_test(tc, is_less_8);
  tcase_add_test(tc, is_equal_1);
  tcase_add_test(tc, is_equal_2);
  tcase_add_test(tc, is_equal_3);
  tcase_add_test(tc, is_equal_4);
  tcase_add_test(tc, is_equal_5);
  tcase_add_test(tc, is_less_or_equal_1);
  tcase_add_test(tc, is_less_or_equal_2);
  tcase_add_test(tc, is_less_or_equal_3);
  tcase_add_test(tc, is_less_or_equal_4);
  tcase_add_test(tc, is_less_or_equal_5);
  tcase_add_test(tc, is_greater_1);
  tcase_add_test(tc, is_greater_2);
  tcase_add_test(tc, is_greater_3);
  tcase_add_test(tc, is_greater_4);
  tcase_add_test(tc, is_greater_or_equal_1);
  tcase_add_test(tc, is_greater_or_equal_2);
  tcase_add_test(tc, is_greater_or_equal_3);
  tcase_add_test(tc, is_greater_or_equal_4);
  tcase_add_test(tc, is_greater_or_equal_5);
  tcase_add_test(tc, is_not_equal_1);
  tcase_add_test(tc, is_not_equal_2);
  tcase_add_test(tc, is_not_equal_3);
  tcase_add_test(tc, is_not_equal_4);
  tcase_add_test(tc, is_not_equal_5);
  tcase_add_test(tc, form_int_to_decimal_1);
  tcase_add_test(tc, form_int_to_decimal_2);
  tcase_add_test(tc, form_int_to_decimal_3);
  tcase_add_test(tc, form_int_to_decimal_4);
  tcase_add_test(tc, form_int_to_decimal_5);
  tcase_add_test(tc, form_float_to_decimal_1);
  tcase_add_test(tc, form_float_to_decimal_2);
  tcase_add_test(tc, form_float_to_decimal_4);
  tcase_add_test(tc, decimal_to_int_2);
  tcase_add_test(tc, decimal_to_int_3);
  tcase_add_test(tc, decimal_to_int_4);
  tcase_add_test(tc, decimal_to_float_1);
  tcase_add_test(tc, decimal_to_float_2);
  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, floor_4);
  tcase_add_test(tc, round_01);
  tcase_add_test(tc, round_02);
  tcase_add_test(tc, round_03);
  tcase_add_test(tc, round_04);
  tcase_add_test(tc, round_05);
  tcase_add_test(tc, round_06);
  tcase_add_test(tc, round_07);
  tcase_add_test(tc, round_08);
  tcase_add_test(tc, round_09);
  tcase_add_test(tc, round_10);
  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, truncate_1);
  tcase_add_test(tc, truncate_2);
  srunner_run_all(sr, CK_ENV);

  int fails = srunner_ntests_failed(sr);

  srunner_free(sr);
  if (fails == 1) flag = 1;

  return flag;
}