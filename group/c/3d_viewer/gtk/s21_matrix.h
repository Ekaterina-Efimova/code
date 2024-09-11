#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>

#include "s21_parce.h"

#define PI 3.14159265358979323846

typedef struct {
  float x, y, z;
} Point;

Point rotate(Point p, double angle_x, double angle_y, double angle_z);
Point rotateX(Point p, double angle);
Point rotateY(Point p, double angle);
Point rotateZ(Point p, double angle);
Point move(Point p, double dx, double dy, double dz);
Point scale(Point p, double factor);

#endif