#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = !result || s21_check_decimal(value);

  if (!error) {
    int power = s21_get_power(value);

    for (; power > 0; power--) {
      s21_div_10(&value);
    }

    *result = value;
    result->bits[3] = s21_get_sign_bit(value) << 31;
  }

  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = s21_truncate(value, result);

  if (!error) {
    s21_sub(value, *result, &value);
    s21_decimal help = {0};

    if (!s21_is_equal(value, help) && s21_get_sign_bit(value)) {
      help.bits[0] = 1;
      s21_sub(*result, help, result);
    }
  }

  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = s21_truncate(value, result);

  if (!error) {
    s21_decimal help = {{0x5, 0x0, 0x0, 0x10000}};
    s21_sub(value, *result, &value);
    s21_clear_sign_bit(&value);

    if (s21_is_greater_or_equal(value, help)) {
      help.bits[0] = 1;
      help.bits[3] = s21_get_sign_bit(*result) << 31;

      error = s21_add(*result, help, result);
    }
  }

  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = !result || s21_check_decimal(value);

  if (!error) {
    *result = value;
    result->bits[3] ^= (1U << 31);
  }

  return error;
}