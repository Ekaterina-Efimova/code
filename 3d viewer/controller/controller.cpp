#include "controller.h"
using namespace s21;

Controller::Controller() {
  model_info = modelinfo();
  setting_info = settinginfo();
}

void Controller::setupOpenGL(QOpenGLWidget *openglwidget) {
  if (openglwidget) {
    m_renderer = new MyOpenGLRenderer(openglwidget, this);
    connect(openglwidget, &QOpenGLWidget::aboutToCompose, m_renderer,
            &MyOpenGLRenderer::initializeGL);
    connect(openglwidget, &QOpenGLWidget::frameSwapped, m_renderer,
            &MyOpenGLRenderer::paintGL);
  }
}

void Controller::update_model_info(QString filename) {
  if (!filename.isEmpty())
    model_info->filename =
        std::make_unique<std::string>(filename.toStdString());

  std::vector<size_t> info = parse_file(*model_info->filename.get());
  model_info->zero_model_info(info[0], info[1]);
}

void Controller::update_model_info(char action, char axis, double value) {
  if (action == 'r') {
    if (axis == 'x') {
      model_info->rotate_x = value;
    } else if (axis == 'y') {
      model_info->rotate_y = value;
    } else if (axis == 'z') {
      model_info->rotate_z = value;
    }

  } else if (action == 't') {
    if (axis == 'x') {
      model_info->trans_x = value;
    } else if (axis == 'y') {
      model_info->trans_y = value;
    } else if (axis == 'z') {
      model_info->trans_z = value;
    }
  }
}

void Controller::update_model_info(int scale) { model_info->scale = scale; }

void Controller::update_setting_info(bool push) {
  if (push) setting_info->save_settings();
}

void Controller::update_setting_info(QColor color) {
  if (color.isValid()) {
    QString colorStr = color.name();
    setting_info->background_color =
        std::make_unique<std::string>(colorStr.toStdString());
  }
}

void Controller::update_setting_info(bool push, bool solid,
                                     std::unique_ptr<std::string> temp,
                                     int value) {
  if (push) {
    setting_info->edges_type = solid ? SOLID_EDGE : DASHED_EDGE;
    if (temp) setting_info->edge_color = std::move(temp);
    setting_info->edge_thickness = value;
  }
}

void Controller::update_setting_info(bool push, bool zero, bool cercle,
                                     bool square,
                                     std::unique_ptr<std::string> temp,
                                     int value) {
  if (push) {
    if (zero)
      setting_info->vertex_type = ZERO;
    else if (cercle)
      setting_info->vertex_type = CERCLE;
    else if (square)
      setting_info->vertex_type = SQUARE;

    if (temp) setting_info->vertex_color = std::move(temp);
    setting_info->vertex_size = value;
  }
}

void Controller::update_setting_info(int value) {
  setting_info->projection_type = value;
}

std::unique_ptr<std::string> Controller::get_filename() {
  return model_info->filename
             ? std::make_unique<std::string>(*model_info->filename)
             : nullptr;
};
