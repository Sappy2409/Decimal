#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  int sign1 = s21_get_sign(value_1), sign2 = s21_get_sign(value_2);
  int exp = s21_get_scale(value_1) + s21_get_scale(value_2);
  for (int i = 0; i < 96; i++) {
    if (s21_get_bits(value_1, i) == 1) {
      s21_add_simple(value_2, *result, result);
    }
    s21_shift_left(&value_2, 1);
  }
  if (result->bits[0] >= 4294967294) error = 1;
  s21_set_scale(result, exp);
  if (sign1 != sign2) s21_set_sign(result, 1);
  if (sign1 == sign2) s21_set_sign(result, 0);
  if (error == 1 && s21_get_sign(*result) == 1) error = 2;
  return error;
}
/// IT WORKS
