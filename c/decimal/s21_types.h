#ifndef S21_TYPES_H
#define S21_TYPES_H

#define DEC_MAX_FLOAT 79228157791897854723898736640.0f
#define MIN_INT \
  { 0x80000000, 0x0, 0x0, 0x80000000 }
#define MAX_INT \
  { 0x7FFFFFFF, 0x0, 0x0, 0x0 }
#define OVERFLOW ((long)1 << 32)
#define BIT_MASK 0b01111111000000001111111111111111

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

typedef struct s21_long_decimal {
  unsigned int bits[8];
} s21_long_decimal;

#endif