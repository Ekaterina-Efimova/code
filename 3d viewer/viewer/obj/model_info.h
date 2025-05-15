#ifndef MODELINFO_H
#define MODELINFO_H

#include <memory>
#include <string>

namespace s21 {
class ModelInfo {
 public:
  // инициализация ModelInfo
  ModelInfo();
  // обновление ModelInfo
  void zero_model_info(int points, int edges);

  std::unique_ptr<std::string> filename;
  int num_vertices;
  int num_edges;
  double trans_x, trans_y, trans_z;
  double rotate_x, rotate_y, rotate_z;
  int scale;
};
}  // namespace s21

#endif  // MODELINFO_H