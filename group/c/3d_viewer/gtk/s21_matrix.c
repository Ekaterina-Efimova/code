#include "s21_matrix.h"

Point rotate(Point p, double angle_x, double angle_y, double angle_z) {
  return rotateX(rotateY(rotateZ(p, angle_z), angle_y), angle_x);
}

Point rotateX(Point p, double angle) {
  double rad = angle * PI / 180.0;
  double cos_a = cos(rad), sin_a = sin(rad);
  Point result = {p.x, p.y * cos_a - p.z * sin_a, p.y * sin_a + p.z * cos_a};

  return result;
}

Point rotateY(Point p, double angle) {
  double rad = angle * PI / 180.0;
  double cos_a = cos(rad), sin_a = sin(rad);
  Point result = {p.x * cos_a + p.z * sin_a, p.y, -p.x * sin_a + p.z * cos_a};

  return result;
}

Point rotateZ(Point p, double angle) {
  double rad = angle * PI / 180.0;
  double cos_a = cos(rad), sin_a = sin(rad);
  Point result = {p.x * cos_a - p.y * sin_a, p.x * sin_a + p.y * cos_a, p.z};

  return result;
}

Point move(Point p, double dx, double dy, double dz) {
  Point result = {p.x + dx, p.y + dy, p.z + dz};

  return result;
}

Point scale(Point p, double factor) {
  if (factor == 0.0) factor = 100.0;
  factor = factor / 100.0;
  Point result = {p.x * factor, p.y * factor, p.z * factor};

  return result;
}