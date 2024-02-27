#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define S21_UINT_MAX 4294967295

typedef struct {
  unsigned int bits[4];
} s21_decimal;

//ВСПОМОГАТЕЛЬНЫЕ
int s21_get_sign(s21_decimal dec);
int s21_get_scale(s21_decimal dec);
void s21_set_scale(s21_decimal *dec, int scale);
void s21_set_bits(s21_decimal *dec, int ind, int bit);
void s21_set_sign(s21_decimal *dec, int bit);
void print_binary(s21_decimal dec);
int s21_get_bits(s21_decimal dec, int ind);
void s21_shift_left(s21_decimal *dec, int shift);
void s21_shift_right(s21_decimal *dec, int shift);
int s21_add_simple(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
int s21_sub_simple(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
void s21_mul_10_scale(s21_decimal *dec);
void s21_div_10_scale(s21_decimal *dec);
int s21_bit_compare(s21_decimal da, s21_decimal db);
void s21_normalize(s21_decimal *dec_1, s21_decimal *dec_2);
int s21_get_high_bit_pos(s21_decimal src);
int find_first_bit(s21_decimal dec);
int s21_last_num_div_10(s21_decimal *dec);

//АРИФМЕТИЧЕСКИЕ
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

//ФУНКЦИИ СРАВНЕНИЯ
int s21_is_less(s21_decimal da, s21_decimal db);
int s21_is_less_or_equal(s21_decimal da, s21_decimal db);
int s21_is_equal(s21_decimal da, s21_decimal db);
int s21_is_greater(s21_decimal da, s21_decimal db);
int s21_is_greater_or_equal(s21_decimal da, s21_decimal db);
int s21_is_not_equal(s21_decimal da, s21_decimal db);

//ФУНКЦИИ ПРЕОБРАЗОВАНИЯ
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

//ДРУГИЕ ФУНКЦИИ
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif
