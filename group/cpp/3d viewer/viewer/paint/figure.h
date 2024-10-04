#ifndef FIGURE_H
#define FIGURE_H

#include <vector>

#include "../obj/obj.hpp"
#undef TINYOBJLOADER_IMPLEMENTATION
#include "../obj/tiny_obj_loader.h"
#include "point.h"
namespace s21 {
class Figure {
 private:
  float min_x, min_y, min_z;
  float max_x, max_y, max_z;

 public:
  std::vector<float> points_file;
  std::vector<unsigned int> edges_file;
  std::vector<float> points;
  std::vector<unsigned int> edges;

  Figure();
  ~Figure();

  void find_min_max_vertices();
  void convert_shapes_to_edges(const std::vector<tinyobj::shape_t> &shapes);
  Figure normalize();
};

inline Figure *get_figure() {
  static Figure fig;
  return &fig;
};
}  // namespace s21
#endif  // FIGURE_H
