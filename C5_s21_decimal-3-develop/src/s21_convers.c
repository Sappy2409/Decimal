#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  int sign = 0;
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  if (src < 0) sign = 1;
  s21_set_sign(dst, sign);
  unsigned int overflow_check = 0b11111111111111111111111111111111;
  if ((unsigned int)src > overflow_check) error = 1;
  if (src < 0) {
    dst->bits[0] = -src;
  } else {
    dst->bits[0] = src;
  }
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  int count = 0;
  int scale = 0;
  float temp_int = 0.0;
  if (isnan(src) || isinf(src)) error = 1;
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  if (!error) {
    if (fabs(src) < 1e-28 || fabs(src) > 79228162514264337593543950335.0) {
      error = 1;
    } else {
      float temp_float = modff(src, &temp_int);
      while (temp_int >= 10000000) {
        temp_int /= 10;
        count = 7;
      }
      float temp_int_1 = fabs(temp_int);
      if (count < 7) {
        while (temp_int_1 >= 1) {
          temp_int_1 /= 10;
          count++;
        }
        scale = 7 - count;
        if (scale <= 7) {
          temp_float *= pow(10, scale);
          temp_int *= pow(10, scale);
          temp_int += temp_float;
        }
      }
      int int_temp = temp_int;
      for (int i = 0; i < 96; i++) {
        s21_set_bits(dst, i, int_temp % 2);
        int_temp /= 2;
      }
      if (src < 0) s21_set_sign(dst, 1);
      s21_set_scale(dst, scale);
    }
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_truncate(src, &src);
  int error = 0;
  if (src.bits[1] != 0 || src.bits[2] != 0) error = 1;
  int sign = s21_get_sign(src);
  *dst = src.bits[0];
  if (sign != 0) *dst *= -1;
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0, scale = s21_get_scale(src),
      hightPos = s21_get_high_bit_pos(src);
  long double buffer = 0;
  if (dst) {
    *dst = 0;
    for (int i = 0; i <= hightPos; i++) {
      buffer += s21_get_bits(src, i) * pow(2, i);
    }
    for (int i = 0; i < scale; i++) {
      buffer /= 10.0;
    }
    *dst = (float)buffer;
    if (s21_get_sign(src)) {
      *dst *= -1;
    }
  } else {
    error = 1;
  }
  return error;
}
