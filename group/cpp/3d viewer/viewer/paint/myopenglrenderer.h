#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <QMessageBox>
#include <QObject>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>
#include <iostream>

#include "../obj/obj.hpp"
#include "figure.h"
namespace s21 {
class MyOpenGLRenderer : public QObject, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit MyOpenGLRenderer(QOpenGLWidget *glWidget, QObject *parent = nullptr);

  void initializeGL();
  void paintGL();

 private:
  QOpenGLWidget *m_glWidget;
  GLuint *shader_program;

  QColor get_color();
  QColor get_edge_color();
  QColor get_points_color();
};
}  // namespace s21
#endif  // OPENGLRENDERER_H
