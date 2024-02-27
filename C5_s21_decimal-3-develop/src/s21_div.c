#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0)
    error = 3;
  int sign1 = s21_get_sign(value_1), sign2 = s21_get_sign(value_2);
  int exp = s21_get_scale(value_1) - s21_get_scale(value_2);
  s21_set_scale(&value_1, 0);
  s21_set_scale(&value_2, 0);
  s21_set_sign(&value_1, 0);
  s21_set_sign(&value_2, 0);
  s21_decimal copy = value_2;
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  int i = 95;
  int j = 95;
  while (s21_get_bits(value_2, j) != 1) {
    j--;
  }
  while (s21_get_bits(value_1, i) != 1) {
    i--;
  }
  while (i >= j) {
    s21_shift_left(&value_2, i - j);
    if (s21_is_greater_or_equal(value_1, value_2)) {
      s21_sub_simple(value_1, value_2, &value_1);
      s21_set_bits(result, i - j, 1);
    } else {
      s21_set_bits(result, i - j, 0);
    }
    value_2 = copy;
    i--;
  }
  s21_set_scale(result, exp);
  if (exp < 0) {
    s21_set_scale(result, 0);
    s21_decimal tmp = {{0}};
    exp = abs(exp);
    int multiply = pow(10, exp);
    s21_from_int_to_decimal(multiply, &tmp);
    s21_mul(*result, tmp, result);
  }
  if (sign1 != sign2) s21_set_sign(result, 1);
  if (sign1 == sign2) s21_set_sign(result, 0);
  if (s21_get_bits(*result, 96) == 1) error = 1;
  if (error == 1 && s21_get_sign(*result) == 1) error = 2;
  return error;
}