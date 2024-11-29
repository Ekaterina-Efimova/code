#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QColor>
#include <QOpenGLWidget>
#include <QString>

#include "../viewer/obj/obj.hpp"
#include "../viewer/obj/parse.h"
#include "../viewer/paint/myopenglrenderer.h"

namespace s21 {
class Controller : public QObject {
  Q_OBJECT
 public:
  Controller();

  void update_model_info(QString filename);
  void update_model_info(char action, char axis, double value);
  void update_model_info(int scale);
  void setupOpenGL(QOpenGLWidget *openglwidget);

  std::unique_ptr<std::string> get_filename();
  int get_vertices() { return model_info->num_vertices; };
  int get_edges() { return model_info->num_edges; };
  double get_trans_x() { return model_info->trans_x; };
  double get_trans_y() { return model_info->trans_y; };
  double get_trans_z() { return model_info->trans_z; };
  double get_rotate_x() { return model_info->rotate_x; };
  double get_rotate_y() { return model_info->rotate_y; };
  double get_rotate_z() { return model_info->rotate_z; };
  int get_scale() { return model_info->scale; };

  void update_setting_info(bool push);
  void update_setting_info(QColor color);
  void update_setting_info(bool push, bool solid,
                           std::unique_ptr<std::string> temp, int value);
  void update_setting_info(bool push, bool zero, bool cercle, bool square,
                           std::unique_ptr<std::string> temp, int value);
  void update_setting_info(int value);

  int get_edges_type() { return setting_info->edges_type; };
  int get_vertex_type() { return setting_info->vertex_type; };
  int get_edge_thickness() { return setting_info->edge_thickness; };
  int get_vertex_size() { return setting_info->vertex_size; };
  int get_projection_type() { return setting_info->projection_type; };

 private:
  ModelInfo *model_info;
  SettingInfo *setting_info;
  MyOpenGLRenderer *m_renderer;
};
}  // namespace s21

#endif  // CONTROLLER_H
