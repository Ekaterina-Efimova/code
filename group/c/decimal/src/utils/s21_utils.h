#ifndef s21_UTILS_H
#define s21_UTILS_H

#include "../s21_types.h"

// abcdefghijklmnopqrstuvwxyz

// Функции вычисления
void s21_add_long(s21_long_decimal a, s21_long_decimal b,
                  s21_long_decimal *result);
void s21_div_long(s21_long_decimal a, s21_long_decimal b,
                  s21_long_decimal *result);
void s21_div_10(s21_decimal *a);
void s21_div_10_long(s21_long_decimal *a);
void s21_mul_long(s21_long_decimal a, s21_long_decimal b,
                  s21_long_decimal *result);
void s21_mul_10(s21_decimal *a);
void s21_mul_10_long(s21_long_decimal *a);
void s21_normalize(s21_long_decimal *a, s21_long_decimal *b);
void s21_sum(s21_long_decimal a, s21_long_decimal b, s21_long_decimal *result);
void s21_swap(s21_long_decimal *a, s21_long_decimal *b);

// Функции сравнения
int s21_is_absoluteless(s21_long_decimal a, s21_long_decimal b);
int s21_is_less_long(s21_long_decimal a, s21_long_decimal b);
int s21_is_not_zero(s21_long_decimal a);
int s21_is_overflow(s21_long_decimal a, int param);
int s21_is_zero(s21_long_decimal a);

// Считывают информацию из десимала
int s21_get_exp_from_str(char *str);
int s21_get_power(s21_decimal src);
int s21_get_power_long(s21_long_decimal src);
unsigned s21_get_sign_bit(s21_decimal src);
unsigned s21_get_sign_bit_long(s21_long_decimal src);
int s21_get_last_digit_long(s21_long_decimal src);

// Изменяют десимал
void s21_add_sign(float src, s21_decimal *dst);
void s21_clear(s21_decimal *decimal);
void s21_clear_long(s21_long_decimal *dst);
void s21_clear_sign_bit(s21_decimal *a);
void s21_clear_sign_bit_long(s21_long_decimal *a);
void s21_shift_left_long(s21_long_decimal *a, int count);
void s21_shift_right_long(s21_long_decimal *a, int count);

// Функции конвертации
int s21_check_decimal(s21_decimal src);
int s21_convert_from_long_decimal(s21_long_decimal src, s21_decimal *dst);
int s21_convert_to_long_decimal(s21_decimal src, s21_long_decimal *dst);
void s21_write_decimal(s21_decimal *dst, char *flt, int exp);
#endif