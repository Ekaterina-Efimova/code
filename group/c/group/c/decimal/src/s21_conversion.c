#include <math.h>

#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = !dst;

  if (!error) {
    s21_clear(dst);
    s21_add_sign(src, dst);
    dst->bits[0] = (unsigned)labs((long)src);
  }

  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = !dst || s21_check_decimal(src);

  if (!error) {
    s21_decimal temp = {0};
    s21_decimal temp_min = {MIN_INT};
    s21_decimal temp_max = {MAX_INT};
    error = s21_truncate(src, &temp);

    if (!error)
      error = s21_is_less(temp, temp_min) || s21_is_greater(temp, temp_max);

    if (!error) {
      *dst = 0;
      // моя гордость! проходит по каждому биту из 32 и переводит в 10 систему
      for (int i = 0; i < 32; i++) {
        if (temp.bits[0] & (1U << i)) {
          *dst += pow(2, i);
        }
      }

      *dst *= (s21_get_sign_bit(src) ? -1 : 1);
    }
  }

  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = !dst || isinf(src) || isnan(src) || (fabsf(src) > DEC_MAX_FLOAT);

  if (!error) {
    s21_clear(dst);
    char flt[64];
    sprintf(flt, "%.6e", fabs(src));
    int exp = s21_get_exp_from_str(flt);

    if (exp < -28) {
      error = 1;

    } else if (exp <= -23) {
      int float_precision = exp + 28;
      sprintf(flt, "%.*e", float_precision, fabsf(src));
      exp = s21_get_exp_from_str(flt);
    }

    if (!error) {
      s21_write_decimal(dst, flt, exp);
      s21_add_sign(src, dst);
    }
  }

  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = !dst || s21_check_decimal(src);

  if (!error) {
    const s21_decimal zero = {0};
    if (s21_is_equal(src, zero)) {
      *dst = s21_get_sign_bit(src) ? -0.0 : 0;

    } else {
      double temp_flt = 0;
      *dst = 0;

      for (int i = 0; i < 96; i++) {
        if (src.bits[i / 32] & (1U << (i % 32))) {
          temp_flt += pow(2, i);
        }
      }

      temp_flt /= pow(10, s21_get_power(src));
      temp_flt *= (s21_get_sign_bit(src) ? -1 : 1);
      *dst = (float)temp_flt;
    }
  }

  return error;
}