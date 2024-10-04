#include "model_info.h"
using namespace s21;

ModelInfo::ModelInfo() {
  rotate_x = 180;
  rotate_y = 180;
  rotate_z = 180;
  scale = 50;
  trans_x = 50;
  trans_y = 50;
  trans_z = 50;
  num_vertices = 0;
  num_edges = 0;
}

void ModelInfo::zero_model_info(int points, int edges) {
  rotate_x = 180;
  rotate_y = 180;
  rotate_z = 180;
  scale = 50;
  trans_x = 50;
  trans_y = 50;
  trans_z = 50;
  num_vertices = points;
  num_edges = edges;
}
