#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, flag = 0;
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  s21_normalize(&value_1, &value_2);
  int NewScale = s21_get_scale(value_1);
  flag = s21_bit_compare(value_1,
                         value_2);  // 1 = (value_1 > value_2), 2 = (value_1 <
                                    // value_2), 0 = (value_1 = value_2)
  if (sign1 == sign2) {  // Если знаки одинаковые, вычитаем из большего меньшее
    if (flag == 1) {
      s21_sub_simple(value_1, value_2, result);
      if (sign1 == 0) {
        s21_set_sign(result, 0);
      } else {
        s21_set_sign(result, 1);
      }
    } else if (flag == 2) {
      s21_sub_simple(value_2, value_1, result);
      if (sign1 == 0) {
        s21_set_sign(result, 1);
      } else {
        s21_set_sign(result, 0);
      }
    } else if (flag == 0) {
      s21_sub_simple(value_1, value_2, result);
      s21_set_sign(result, 0);
    }
  } else if (sign1 != sign2) {  //Если знаки разные, складываем и ставим знак
                                //первого числа
    int tmp_sign = s21_get_sign(value_1);
    s21_add_simple(value_1, value_2, result);
    s21_set_sign(result, tmp_sign);
  }
  s21_set_scale(result, NewScale);
  if (s21_get_bits(*result, 96) == 1) error = 1;
  if (error == 1 && s21_get_sign(*result) == 1) error = 2;
  return error;
}