#ifndef POINT_H
#define POINT_H

#define _USE_MATH_DEFINES
#include <cmath>
namespace s21 {
class Point {
 private:
  void rotateX(float angle);
  void rotateY(float angle);
  void rotateZ(float angle);

 public:
  Point(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z){};

  float x, y, z;

  void rotate(float angle_x, float angle_y, float angle_z);
  void move(float dx, float dy, float dz);
  void scale(float factor);
};
}  // namespace s21
#endif  // POINT_H
