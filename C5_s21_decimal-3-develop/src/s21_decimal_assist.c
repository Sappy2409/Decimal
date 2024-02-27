#include "s21_decimal.h"

int s21_get_bits(s21_decimal dec, int ind) {
  return (dec.bits[ind / 32] >> (ind % 32)) & 1u;
}

void s21_set_bits(s21_decimal *dec, int ind, int bit) {
  int mask = 1u << (ind % 32);
  if (bit == 0) {
    dec->bits[ind / 32] = dec->bits[ind / 32] & ~mask;
  } else {
    dec->bits[ind / 32] = dec->bits[ind / 32] | mask;
  }
}

int s21_get_sign(s21_decimal dec) { return s21_get_bits(dec, 127); }

void s21_set_sign(s21_decimal *dec, int bit) {
  int mask = 1u << 31;
  if (bit == 0) {
    dec->bits[3] = dec->bits[3] & ~mask;
  } else {
    dec->bits[3] = dec->bits[3] | mask;
  }
}

int s21_get_scale(s21_decimal dec) { return (dec.bits[3] >> 16) & 127; }

void s21_set_scale(s21_decimal *dec, int scale) {
  int sign = s21_get_sign(*dec);
  dec->bits[3] = scale << 16;
  s21_set_sign(dec, sign);
}

void s21_shift_left(s21_decimal *dec, int shift) {
  for (int i = 0; i < shift; i++) {
    int dec_31 = s21_get_bits(*dec, 31);
    int dec_63 = s21_get_bits(*dec, 63);
    dec->bits[0] <<= 1u;
    dec->bits[1] <<= 1u;
    s21_set_bits(dec, 32, dec_31);
    dec->bits[2] <<= 1u;
    s21_set_bits(dec, 64, dec_63);
  }
}

//если первое число больше то 1, если меньше то 2
int s21_bit_compare(s21_decimal da, s21_decimal db) {
  int flag = 0, bit_a = 0, bit_b = 0;
  for (int i = 95; i >= 0 && flag == 0; i--) {
    bit_a = s21_get_bits(da, i);
    bit_b = s21_get_bits(db, i);
    if (bit_a > bit_b) {
      flag = 1;
    } else if (bit_a < bit_b) {
      flag = 2;
    } else {
      flag = 0;
    }
  }
  return flag;
}

//обычное сложение. вернет единицу, если будет переполнение
int s21_add_simple(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int flag = 0;
  int bit_v_ume = 0;
  for (int i = 0; i <= 96; i++) {
    int x = s21_get_bits(value_1, i);
    int y = s21_get_bits(value_2, i);
    if (i == 96 && (x == 1 || y == 1)) flag = 1;
    if (flag == 0) {
      if (x == 1 && y == 1 && bit_v_ume == 1) {
        s21_set_bits(result, i, 1);
        bit_v_ume = 1;
      } else if (x == 1 && y == 1 && bit_v_ume == 0) {
        s21_set_bits(result, i, 0);
        bit_v_ume = 1;
      } else if (x != y && bit_v_ume == 1) {
        s21_set_bits(result, i, 0);
        bit_v_ume = 1;
      } else if (x == 0 && y == 0 && bit_v_ume == 1) {
        s21_set_bits(result, i, 1);
        bit_v_ume = 0;
      } else if (x == 0 && y == 0 && bit_v_ume == 0) {
        s21_set_bits(result, i, 0);
        bit_v_ume = 0;
      } else if (x != y && bit_v_ume == 0) {
        s21_set_bits(result, i, 1);
        bit_v_ume = 0;
      }
      if (result->bits[3] == 1) flag = 1;
    }
  }
  return flag;
}

//Здесь косяк
int s21_sub_simple(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int error = 0;
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  int res = 0;
  int bit_v_ume = 0;
  int size_dec = 95;
  while (s21_get_bits(value_1, size_dec) != 1) {
    size_dec--;
  }
  for (int i = 0; i <= size_dec; i++) {
    int x = s21_get_bits(value_1, i);
    int y = s21_get_bits(value_2, i);
    res = x - y - bit_v_ume;
    if (res < 0) {
      bit_v_ume = 1;
    } else {
      bit_v_ume = 0;
    }
    res = abs(res);
    s21_set_bits(result, i, res % 2);
  }
  return error;
}

void s21_mul_10_scale(s21_decimal *dec) {
  s21_decimal buffer1 = *dec, buffer2 = *dec;
  s21_shift_left(&buffer1, 3);
  s21_shift_left(&buffer2, 1);
  s21_add_simple(buffer1, buffer2, dec);
  int scale = s21_get_scale(*dec) + 1;
  s21_set_scale(dec, scale);
}

void s21_div_10_scale(s21_decimal *dec) {
  s21_decimal numb = {{10, 0, 0, 0}};
  s21_div(*dec, numb, dec);
  int scale = s21_get_scale(*dec) - 1;
  s21_set_scale(dec, scale);
}

void s21_normalize(s21_decimal *dec_1, s21_decimal *dec_2) {
  int scale1 = s21_get_scale(*dec_1), scale2 = s21_get_scale(*dec_2), min_scale;
  while (scale1 != scale2) {
    int scale_delta = abs(scale1 - scale2);
    if (scale1 < scale2) {
      min_scale = scale1;
      if ((min_scale + scale_delta) < 29) {
        s21_mul_10_scale(dec_1);
        scale1 = s21_get_scale(*dec_1);
      } else {
        s21_div_10_scale(dec_2);
        scale2 = s21_get_scale(*dec_2);
      }
    } else if (scale1 > scale2) {
      min_scale = scale2;
      if ((min_scale + scale_delta) < 29) {
        s21_mul_10_scale(dec_2);
        scale2 = s21_get_scale(*dec_2);
      } else {
        s21_div_10_scale(dec_1);
        scale1 = s21_get_scale(*dec_1);
      }
    }
  }
}

int s21_get_high_bit_pos(s21_decimal src) {
  int highBitPos = -1;
  for (int i = 0; i < 3 * 32; i++) {
    if ((src.bits[i / 32] & (1u << (i % 32))) != 0) {
      highBitPos = i;
    }
  }
  return highBitPos;
}

int find_first_bit(s21_decimal dec) {
  int number_bit = 0;
  for (int i = 95; i >= 0; i--) {
    if (!number_bit && s21_get_bits(dec, i)) {
      number_bit = i;
    }
  }
  return number_bit;
}

int s21_last_num_div_10(s21_decimal *dec) {
  int ost = 0;
  for (int i = 95; i >= 0; --i) {
    int bit = s21_get_bits(*dec, i);
    int new = (bit + ost * 2) / 10;
    ost = (bit + ost * 2) % 10;
    s21_set_bits(dec, i, new);
  }
  return ost;
}