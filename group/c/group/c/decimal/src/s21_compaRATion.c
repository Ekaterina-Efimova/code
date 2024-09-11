#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal a, b;
  s21_convert_to_long_decimal(value_1, &a);
  s21_convert_to_long_decimal(value_2, &b);

  return s21_is_less_long(a, b);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_2, value_1);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  return !(s21_is_less(value_1, value_2) || s21_is_less(value_2, value_1));
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
