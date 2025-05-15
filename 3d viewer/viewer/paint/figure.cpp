#include "figure.h"
using namespace s21;

Figure::Figure() {
  min_x = __FLT_MAX__;
  min_y = __FLT_MAX__;
  min_z = __FLT_MAX__;
  max_x = -__FLT_MAX__;
  max_y = -__FLT_MAX__;
  max_z = -__FLT_MAX__;
}

Figure::~Figure() {
  points_file.clear();
  edges_file.clear();
  points.clear();
  edges.clear();
}

void Figure::find_min_max_vertices() {
  min_x = points_file[0];
  min_y = points_file[1];
  min_z = points_file[2];
  max_x = points_file[0];
  max_y = points_file[1];
  max_z = points_file[2];
  for (size_t i = 0; i < points_file.size(); i += 3) {
    min_x = std::min(min_x, points_file[i]);
    min_y = std::min(min_y, points_file[i + 1]);
    min_z = std::min(min_z, points_file[i + 2]);
    max_x = std::max(max_x, points_file[i]);
    max_y = std::max(max_y, points_file[i + 1]);
    max_z = std::max(max_z, points_file[i + 2]);
  }
}

void Figure::convert_shapes_to_edges(
    const std::vector<tinyobj::shape_t>& shapes) {
  edges_file.clear();
  for (const auto& shape : shapes) {
    size_t index = 0;
    for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
      size_t fv = shape.mesh.num_face_vertices[f];
      tinyobj::index_t first, idx, idx_next;
      for (size_t i = 0; i < fv; i++, index++) {
        if (i == 0) first = shape.mesh.indices[index];

        idx = shape.mesh.indices[index];
        idx_next = ((i != fv - 1) ? shape.mesh.indices[index + 1] : first);
        edges_file.push_back(idx.vertex_index);
        edges_file.push_back(idx_next.vertex_index);
      }
    }
  }
}

Figure Figure::normalize() {
  ModelInfo* info = modelinfo();

  points = std::vector<float>(points_file);
  edges = std::vector<unsigned int>(edges_file);

  float x_center = (min_x + max_x) / 2;
  float y_center = (min_y + max_y) / 2;
  float z_center = (min_z + max_z) / 2;

  float scale = (float)(pow(10, info->scale / 25.0) / 100) / 1.1;
  float x = (max_x - min_x) / 2;  // x scale
  float y = (max_y - min_y) / 2;  // y scale
  float z = (max_z - min_z) / 2;  // z scale
  if (x == 0) x = 0.01;
  if (y == 0) y = 0.01;
  if (z == 0) z = 0.01;
  scale /= (x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z);

  for (size_t i = 0; i < points.size(); i += 3) {
    Point point = {points[i] - x_center, points[i + 1] - y_center,
                   points[i + 2] - z_center};

    point.rotate(info->rotate_x, info->rotate_y, info->rotate_z);
    point.move((info->trans_x - 50.0) / 30 / scale,
               (info->trans_y - 50.0) / 30 / scale,
               (info->trans_z - 50.0) / 30 / scale);
    point.scale(scale);

    points[i] = point.x;
    points[i + 1] = point.y;
    points[i + 2] = point.z;
  }

  return *this;
}
