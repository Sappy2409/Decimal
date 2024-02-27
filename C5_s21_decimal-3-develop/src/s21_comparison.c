#include "s21_decimal.h"

int s21_is_less(s21_decimal da, s21_decimal db) {
  int flag = 0, sign_a = s21_get_sign(da), sign_b = s21_get_sign(db);
  if (sign_a > sign_b) {
    flag = 1;
  } else if (sign_a < sign_b) {
    flag = 0;
  } else {
    s21_normalize(&da, &db);
    if (s21_bit_compare(da, db) == 2) {
      flag = 1;
      if (sign_a == 1) flag = 0;
    } else {
      flag = 0;
      if (sign_a == 1) flag = 1;
    }
  }
  return flag;
}

int s21_is_equal(s21_decimal da, s21_decimal db) {
  int flag = 0;
  int sign1 = s21_get_sign(da), sign2 = s21_get_sign(db);
  s21_normalize(&da, &db);
  if (sign1 != sign2) {
    flag = 0;
  } else if (da.bits[3] == db.bits[3] && da.bits[2] == db.bits[2] &&
             da.bits[1] == db.bits[1] && da.bits[0] == db.bits[0]) {
    flag = 1;
  } else {
    flag = 0;
  }
  return flag;
}

int s21_is_less_or_equal(s21_decimal da, s21_decimal db) {
  return (s21_is_less(da, db) || s21_is_equal(da, db));
}

int s21_is_greater(s21_decimal da, s21_decimal db) {
  return (!s21_is_less(da, db) && !s21_is_equal(da, db));
}

int s21_is_greater_or_equal(s21_decimal da, s21_decimal db) {
  return (s21_is_greater(da, db) || s21_is_equal(da, db));
}

int s21_is_not_equal(s21_decimal da, s21_decimal db) {
  return (!s21_is_equal(da, db));
}