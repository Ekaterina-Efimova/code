#include "s21_parce.h"

bool parce_param(char *filename) {
  Parametrs *param = get_param();
  init_param(param);

  bool err = SUCCESS;
  FILE *file = fopen(filename, "r");
  if (file == NULL || param == NULL)
    err = FAIL_FILE_READ;
  else {
    int sym;
    while ((sym = fgetc(file)) != EOF) {
      if (sym == 'v' && (sym = fgetc(file)) == ' ') {
        parce_v(file, param, &sym);
      } else if (sym == 'f' && (sym = fgetc(file)) == ' ') {
        parce_f(file, param, &sym);
      }
    }
  }
  if (file != NULL) fclose(file);

  return err;
}

Parametrs *get_param() {
  static Parametrs param = {0};
  static int first_time = true;
  if (first_time) {
    first_time = false;
    compasity_for_param(&param);
    init_param(&param);
  }

  return &param;
}

void compasity_for_param(Parametrs *param) {
  param->edges = malloc(START_CAPACITY * sizeof(int));
  param->points = malloc(START_CAPACITY * sizeof(float));
  if (!(param->edges) || !(param->points)) exit(FAIL_MALLOC);
}
void init_param(Parametrs *param) {
  param->count_edges = 0;
  param->count_points = 0;
  param->min_max_x[0] = param->min_max_y[0] = param->min_max_z[0] = FLT_MAX;
  param->min_max_x[1] = param->min_max_y[1] = param->min_max_z[1] = FLT_MIN;
}

void free_param(Parametrs *param) {
  if (param) {
    if (param->edges) {
      free(param->edges);
      param->edges = NULL;
    }
    if (param->points) {
      free(param->points);
      param->points = NULL;
    }
  }
}

void realloc_points(Parametrs *param, int count) {
  static int current_limit = START_CAPACITY;
  if (count >= current_limit - 1) {
    current_limit *= 2;
    param->points = realloc(param->points, current_limit * sizeof(float));

    if (param->points == NULL) exit(FAIL_REALLOC_POINT);
  }
}

void realloc_edges(Parametrs *param, int count) {
  static int current_limit = START_CAPACITY;
  if (count >= current_limit - 1) {
    current_limit *= 2;
    param->edges = realloc(param->edges, current_limit * sizeof(int));

    if (param->edges == NULL) exit(FAIL_REALLOC_EDGE);
  }
}

void get_shift(FILE *file, int *sym) {
  if (*sym != ' ' && *sym != '\n' && *sym != EOF) {
    while (((*sym = fgetc(file)) != ' ') && *sym != EOF && *sym != '\n') {
      ;
    }
  }
}

void get_digit_part(FILE *file, int *index, char *buff, int *sym) {
  if (isdigit(*sym)) buff[(*index)++] = *sym;
  for (; isdigit(*sym = fgetc(file)); (*index)++) {
    buff[*index] = *sym;
  }
}

void get_exp_part(FILE *file, int *index, char *buff, int *sym) {
  buff[(*index)++] = *sym;
  buff[(*index)++] = (*sym = fgetc(file));
  get_digit_part(file, index, buff, sym);
}

float get_digit(FILE *file, int mode, int *sym) {
  int index = 0;
  char buff[100] = {'\0'};
  int sign = 1;
  if ((*sym = fgetc(file)) == '-') sign = -1;
  get_digit_part(file, &index, buff, sym);
  if (mode == 1) {
    if (*sym == '.') {
      buff[index++] = *sym;
      get_digit_part(file, &index, buff, sym);
      if (*sym == 'e') get_exp_part(file, &index, buff, sym);
    }
  }
  if (mode == 2 && *sym != '\n') {
    get_shift(file, sym);
  }
  return strtof(buff, NULL) * sign;
}

void parce_v(FILE *file, Parametrs *param, int *sym) {
  int count = param->count_points * 3;
  realloc_points(param, count + 4);

  if (fscanf(file, "%f", &param->points[count]) != 1) printf("error %d", count);
  if (param->points[count] < param->min_max_x[0]) {
    param->min_max_x[0] = param->points[count];
  }
  if (param->points[count] > param->min_max_x[1]) {
    param->min_max_x[1] = param->points[count];
  }

  count++;
  if (fscanf(file, "%f", &param->points[count]) != 1) printf("error %d", count);
  if (param->points[count] < param->min_max_y[0]) {
    param->min_max_y[0] = param->points[count];
  }
  if (param->points[count] > param->min_max_y[1]) {
    param->min_max_y[1] = param->points[count];
  }

  count++;
  if (fscanf(file, "%f", &param->points[count]) != 1) printf("error %d", count);
  if (param->points[count] < param->min_max_z[0]) {
    param->min_max_z[0] = param->points[count];
  }
  if (param->points[count] > param->min_max_z[1]) {
    param->min_max_z[1] = param->points[count];
  }
  param->count_points++;
}

void parce_f(FILE *file, Parametrs *param, int *sym) {
  int count = param->count_edges * 2;
  int try = 0;

  while (*sym != '\n' && *sym != EOF) {
    realloc_edges(param, count + 3);
    if (try > 1) {
      param->edges[count] = param->edges[count - 1];
      count++;
      param->count_edges++;
    }
    if (fscanf(file, "%d/%*d/%*d", &param->edges[count]) == 0) {
      fscanf(file, "%d", &param->edges[count]);
    }
    *sym = fgetc(file);
    count++;
    try++;
  }

  param->count_edges++;
}