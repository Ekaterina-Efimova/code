#include "s21_utils.h"

#include "../s21_decimal.h"

void s21_add_long(s21_long_decimal a, s21_long_decimal b,
                  s21_long_decimal *result) {
  s21_normalize(&a, &b);

  if (s21_is_absoluteless(a, b)) {
    s21_swap(&a, &b);
  }

  s21_sum(a, b, result);

  result->bits[7] = a.bits[7];
}

void s21_div_long(s21_long_decimal a, s21_long_decimal b,
                  s21_long_decimal *result) {
  s21_clear_long(result);
  unsigned sign_bit = s21_get_sign_bit_long(a) ^ s21_get_sign_bit_long(b);
  int power = s21_get_power_long(a) - s21_get_power_long(b);
  a.bits[7] = 0;
  b.bits[7] = 1U << 31;

  int result_bit = 0;
  s21_long_decimal subtract = b;
  while (s21_is_absoluteless(subtract, a)) {
    s21_shift_left_long(&subtract, 1);
    result_bit++;
  }

  while (!s21_is_absoluteless(a, b)) {
    while (s21_is_absoluteless(a, subtract)) {
      s21_shift_right_long(&subtract, 1);
      result_bit--;
    }

    s21_sum(a, subtract, &a);
    s21_long_decimal one_bit = {0};
    one_bit.bits[result_bit / 32] = 1 << (result_bit % 32);
    s21_sum(*result, one_bit, result);
  }

  subtract = b;
  while (!s21_is_overflow(*result, 4) && (power < 30) && s21_is_not_zero(a)) {
    s21_mul_10_long(&a);
    s21_mul_10_long(result);
    power++;

    while (!s21_is_absoluteless(a, b)) {
      const s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
      s21_sum(a, subtract, &a);
      s21_sum(*result, one, result);
    }
  }

  for (; power < 0; power++) {
    s21_mul_10_long(result);
  }

  result->bits[7] = (sign_bit << 31) + (power << 16) + s21_is_not_zero(a);
}

void s21_div_10(s21_decimal *a) {
  s21_long_decimal a_l;

  s21_convert_to_long_decimal(*a, &a_l);
  s21_div_10_long(&a_l);
  s21_convert_from_long_decimal(a_l, a);
}

void s21_div_10_long(s21_long_decimal *a) {
  const s21_long_decimal ten = {{10, 0, 0, 0, 0, 0, 0, (1U << 31)}};
  s21_long_decimal result = {0};
  int temp = a->bits[7];
  a->bits[7] = 0;

  int result_bit = 0;
  s21_long_decimal subtract = ten;
  while (s21_is_absoluteless(subtract, *a) && result_bit < 188) {
    s21_shift_left_long(&subtract, 1);
    result_bit++;
  }

  while (!s21_is_absoluteless(*a, ten)) {
    while (s21_is_absoluteless(*a, subtract)) {
      s21_shift_right_long(&subtract, 1);
      result_bit--;
    }

    s21_add_long(*a, subtract, a);
    result.bits[result_bit / 32] |= 1U << (result_bit % 32);
  }

  *a = result;
  a->bits[7] = temp;
}

void s21_mul_long(s21_long_decimal a, s21_long_decimal b,
                  s21_long_decimal *result) {
  s21_clear_long(result);
  result->bits[7] = a.bits[7];

  int shifted = 0;
  for (int i = 0; i < 192 && s21_is_not_zero(b); i++) {
    if (b.bits[i / 32] & 1) {
      s21_shift_left_long(&a, i - shifted);
      shifted = i;

      s21_sum(a, *result, result);
    }

    b.bits[i / 32] >>= 1;
  }

  result->bits[7] = (s21_get_sign_bit_long(a) ^ s21_get_sign_bit_long(b)) << 31;
  result->bits[7] += (s21_get_power_long(a) + s21_get_power_long(b)) << 16;
}

void s21_mul_10(s21_decimal *a) {
  s21_long_decimal a_l;

  s21_convert_to_long_decimal(*a, &a_l);
  s21_mul_10_long(&a_l);
  s21_convert_from_long_decimal(a_l, a);
}

void s21_mul_10_long(s21_long_decimal *a) {
  s21_shift_left_long(a, 1);
  s21_long_decimal temp = *a;
  s21_shift_left_long(a, 2);
  s21_sum(*a, temp, a);
}

void s21_normalize(s21_long_decimal *a, s21_long_decimal *b) {
  int power_diff = s21_get_power_long(*a) - s21_get_power_long(*b);

  if (power_diff > 0) {
    b->bits[7] += power_diff << 16;

    for (; power_diff > 0; power_diff--) {
      s21_mul_10_long(b);
    }

  } else {
    a->bits[7] += -power_diff << 16;

    for (; power_diff < 0; power_diff++) {
      s21_mul_10_long(a);
    }
  }
}

void s21_sum(s21_long_decimal a, s21_long_decimal b, s21_long_decimal *result) {
  int sign = (s21_get_sign_bit_long(a) ^ s21_get_sign_bit_long(b)) ? -1 : 1;
  int overflow = 0;

  for (int i = 0; i <= 6; i++) {
    unsigned long int temp;

    temp = a.bits[i] + (long)sign * b.bits[i] + overflow + OVERFLOW;
    result->bits[i] = temp & 0xFFFFFFFF;

    if (temp >= OVERFLOW << 1) {  // если переполнение при сложении
      overflow = 1;
    } else if (temp < OVERFLOW) {  // если нужно занять бит при вычитании
      overflow = -1;
    } else {
      overflow = 0;
    }
  }
}

void s21_swap(s21_long_decimal *a, s21_long_decimal *b) {
  s21_long_decimal temp;

  temp = *a;
  *a = *b;
  *b = temp;
}

int s21_is_absoluteless(s21_long_decimal a, s21_long_decimal b) {
  s21_clear_sign_bit_long(&a);
  s21_clear_sign_bit_long(&b);

  return s21_is_less_long(a, b);
}

int s21_is_less_long(s21_long_decimal a, s21_long_decimal b) {
  int result = 0;
  int stop = (s21_is_zero(a) && s21_is_zero(b));

  if (!stop) {
    s21_normalize(&a, &b);
    int sign_a = s21_get_sign_bit_long(a);
    int sign_b = s21_get_sign_bit_long(b);

    if (sign_a && sign_b) s21_swap(&a, &b);
    a.bits[7] = sign_b;
    b.bits[7] = sign_a;

    for (int i = 7; i >= 0 && !stop; i--) {
      if (a.bits[i] < b.bits[i]) {
        result = 1;
        stop = 1;

      } else if (a.bits[i] > b.bits[i]) {
        stop = 1;
      }
    }
  }

  return result;
}

int s21_is_not_zero(s21_long_decimal a) {
  return a.bits[6] || a.bits[5] || a.bits[4] || a.bits[3] || a.bits[2] ||
         a.bits[1] || a.bits[0];
}

int s21_is_overflow(s21_long_decimal a, int param) {
  int result = 0;

  for (int i = 6; i >= param && !result; i--) {
    result = !!a.bits[i];
  }

  return result;
}

int s21_is_zero(s21_long_decimal a) { return !s21_is_not_zero(a); }

int s21_get_exp_from_str(char *str) {
  int result = 0;
  char *ptr = str;

  while (*ptr != '\0' && *ptr != 'e') {
    ptr++;
  }

  if (*ptr == 'e') {
    ++ptr;
    result = strtol(ptr, NULL, 10);
  }

  return result;
}

int s21_get_power(s21_decimal src) { return (src.bits[3] << 1) >> 17; }

int s21_get_power_long(s21_long_decimal src) {
  return (src.bits[7] << 1) >> 17;
}

unsigned s21_get_sign_bit(s21_decimal src) { return src.bits[3] >> 31; }

unsigned s21_get_sign_bit_long(s21_long_decimal src) {
  return src.bits[7] >> 31;
}

int s21_get_last_digit_long(s21_long_decimal src) {
  int num = 0;
  int last_bit_digit = 1;

  while (s21_is_not_zero(src)) {
    if (src.bits[0] & 1) {
      num += last_bit_digit;
    }

    s21_shift_right_long(&src, 1);
    last_bit_digit <<= 1;
    if (last_bit_digit > 9) last_bit_digit -= 10;
  }

  return num % 10;
}

void s21_add_sign(float src, s21_decimal *dst) {
  if (signbit(src)) {
    dst->bits[3] |= 1U << 31;

  } else {  // если придется сбросить знак
    dst->bits[3] &= 0x7FFFFFFF;
  }
}

void s21_clear(s21_decimal *dst) {
  for (int i = 0; i <= 3; i++) {
    dst->bits[i] = 0;
  }
}

void s21_clear_long(s21_long_decimal *dst) {
  for (int i = 0; i <= 7; i++) {
    dst->bits[i] = 0;
  }
}

void s21_clear_sign_bit(s21_decimal *a) { a->bits[3] = (a->bits[3] << 1) >> 1; }

void s21_clear_sign_bit_long(s21_long_decimal *a) {
  a->bits[7] = (a->bits[7] << 1) >> 1;
}

void s21_shift_left_long(s21_long_decimal *a, int count) {
  for (int i = 0; i < count; i++) {
    unsigned overflow[8] = {0};

    for (int j = 0; j <= 6; j++) {
      overflow[j + 1] = a->bits[j] >> 31;

      a->bits[j] = (a->bits[j] << 1) + overflow[j];
    }
  }
}

void s21_shift_right_long(s21_long_decimal *a, int count) {
  for (int i = 0; i < count; i++) {
    unsigned overflow[8] = {0};

    for (int j = 6; j >= 0; j--) {
      overflow[j] = a->bits[j] & 1;

      a->bits[j] = (overflow[j + 1] << 31) + (a->bits[j] >> 1);
    }
  }
}

int s21_check_decimal(s21_decimal src) {
  int power = s21_get_power(src);

  return (src.bits[3] & BIT_MASK) || (power < 0 || power > 28);
}

int s21_convert_from_long_decimal(s21_long_decimal src, s21_decimal *dst) {
  unsigned sign_bit = s21_get_sign_bit_long(src);
  int power = s21_get_power_long(src);
  int tail = src.bits[7] & 1;
  int digit = 0;
  src.bits[7] = 0;

  while (power >= 0 && s21_is_overflow(src, 3)) {
    if (digit) tail = 1;
    digit = s21_get_last_digit_long(src);
    s21_div_10_long(&src);
    power--;
  }

  for (; power > 28; power--) {
    if (digit) tail = 1;
    digit = s21_get_last_digit_long(src);
    s21_div_10_long(&src);
  }

  if ((digit > 5) || (digit == 5 && (tail || (src.bits[0] & 1)))) {
    const s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
    s21_sum(src, one, &src);

    if (src.bits[3]) {
      s21_div_10_long(&src);
      power--;
    }
  }

  if (power >= 0) {
    dst->bits[3] = (sign_bit << 31) + (power << 16);
    dst->bits[2] = src.bits[2];
    dst->bits[1] = src.bits[1];
    dst->bits[0] = src.bits[0];
  }

  return (power < 0) ? (1 + sign_bit) : 0;
}

int s21_convert_to_long_decimal(s21_decimal src, s21_long_decimal *dst) {
  int error = s21_check_decimal(src);

  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = 0;
  dst->bits[4] = 0;
  dst->bits[5] = 0;
  dst->bits[6] = 0;
  dst->bits[7] = src.bits[3];

  return error;
}

void s21_write_decimal(s21_decimal *dst, char *flt, int exp) {
  int power = 6;
  int error = 0;

  while (*flt && !error) {
    if (*flt == '.') {
      ++flt;

    } else if (*flt >= '0' && *flt <= '9') {
      int num = (*flt - '0') * pow(10, power);
      s21_decimal temp = {0};
      s21_from_int_to_decimal(num, &temp);
      s21_add(*dst, temp, dst);
      power--;
      ++flt;

    } else {
      error = 1;
    }
  }

  exp -= 6;

  for (; exp > 0; exp--) s21_mul_10(dst);
  for (; exp < -28; exp++) s21_div_10(dst);

  dst->bits[3] += (-exp) << 16;
}