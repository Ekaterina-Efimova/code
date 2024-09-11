#include "s21_decimal.h"

#include "utils/s21_utils.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_long_decimal a = {0};
  s21_long_decimal b = {0};
  s21_long_decimal long_result = {0};

  int error = !(result);
  if (!error) error = s21_convert_to_long_decimal(value_1, &a);
  if (!error) error = s21_convert_to_long_decimal(value_2, &b);
  if (!error) {
    s21_add_long(a, b, &long_result);
    error = s21_convert_from_long_decimal(long_result, result);
  }

  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_negate(value_2, &value_2);

  return s21_add(value_1, value_2, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_long_decimal a = {0};
  s21_long_decimal b = {0};
  s21_long_decimal long_result = {0};

  int error = !(result);
  if (!error) error = s21_convert_to_long_decimal(value_1, &a);
  if (!error) error = s21_convert_to_long_decimal(value_2, &b);
  if (!error) {
    s21_mul_long(a, b, &long_result);
    error = s21_convert_from_long_decimal(long_result, result);
  }

  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_long_decimal a = {0};
  s21_long_decimal b = {0};
  s21_long_decimal long_result = {0};

  int error = !(value_2.bits[2] || value_2.bits[1] || value_2.bits[0]) * 3;
  if (!error) error = !(result);
  if (!error) error = s21_convert_to_long_decimal(value_1, &a);
  if (!error) error = s21_convert_to_long_decimal(value_2, &b);
  if (!error) {
    s21_div_long(a, b, &long_result);
    error = s21_convert_from_long_decimal(long_result, result);
  }

  return error;
}