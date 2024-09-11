#ifndef S21_PARCE_H
#define S21_PARCE_H

#include <ctype.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// errors code

#define SUCCESS 0
#define FAIL_FILE_READ true
#define FAIL_MALLOC 1
#define FAIL_REALLOC_POINT 2
#define FAIL_REALLOC_EDGE 4

#define START_CAPACITY 1000

typedef struct {
  float* points;
  int* edges;
  int count_points;
  int count_edges;
  float min_max_x[2];
  float min_max_y[2];
  float min_max_z[2];
} Parametrs;

// Singletone for struct
Parametrs *get_param();
// Основная ф-ция парсинга, ввозвращает код ошибки при работе с памятью
bool parce_param(char *filename);
// заполняем структуру с полигонами
void parce_f(FILE *file, Parametrs *param, int *sym);
//
void parce_v(FILE *file, Parametrs *param, int *sym);
//
float get_digit(FILE *file, int mode, int *sym);
//
void get_digit_part(FILE *file, int *index, char *buff, int *sym);
//
void get_shift(FILE *file, int *sym);
//
void realloc_edges(Parametrs *param, int count);
//
void realloc_points(Parametrs *param, int count);
//
int realloc_f(Parametrs *param, int *max_dots);
//
void compasity_for_param(Parametrs *param);
void init_param(Parametrs *param);

void free_param(Parametrs *param);

void get_exp_part(FILE *file, int *index, char *buff, int *sym);

#endif