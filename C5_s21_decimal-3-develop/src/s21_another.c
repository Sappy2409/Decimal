#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  *result = value;
  int sign = s21_get_sign(value);
  if (sign == 0) {
    s21_set_sign(result, 1);
  } else {
    s21_set_sign(result, 0);
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  while (s21_get_scale(value) > 0) {
    s21_div_10_scale(&value);
  }
  *result = value;
  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int sign = s21_get_sign(value), scale = s21_get_scale(value), error = 0;
  if (result) {
    s21_truncate(value, result);
    if (sign && scale) {
      s21_set_bits(result, 127, 0);
      s21_decimal one = {{1, 0, 0, 0}};
      error = s21_add_simple(*result, one, result);
      s21_set_sign(result, 1);
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int sign = s21_get_sign(value), scale = s21_get_scale(value), error = 0;
  s21_set_sign(&value, 0);
  int rem = 0;
  s21_truncate(value, result);
  for (int i = 0; i < scale; i++) {
    rem = s21_last_num_div_10(&value);
  }
  if (rem >= 5) {
    s21_decimal one = {{1, 0, 0, 0}};
    error = s21_add_simple(*result, one, result);
  }
  if (sign) s21_set_sign(result, 1);
  return error;
}