#include "myopenglrenderer.h"
using namespace s21;

MyOpenGLRenderer::MyOpenGLRenderer(QOpenGLWidget *glWidget, QObject *parent)
    : QObject(parent), m_glWidget(glWidget) {
  shader_program = new GLuint;
}

void MyOpenGLRenderer::initializeGL() {
  m_glWidget->makeCurrent();
  initializeOpenGLFunctions();
  SettingInfo &settings = *settinginfo();
  QColor color = get_color();
  glClearColor(color.redF(), color.greenF(), color.blueF(), 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Figure fig = get_figure()->normalize();
  glVertexPointer(3, GL_FLOAT, 0, fig.points.data());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (settings.projection_type == 0) {
    glFrustum(-1, 1, -1, 1, 1, 1000);
    glTranslatef(0, 0, -2);
  }

  glEnableClientState(GL_VERTEX_ARRAY);

  if (settings.vertex_type) {
    glPointSize(settings.vertex_size);
    color = get_points_color();
    glColor3f(color.redF(), color.greenF(), color.blueF());
    glDrawArrays(GL_POINTS, 0, fig.points.size() / 3);
  }

  if (settinginfo()->edges_type) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }
  glLineWidth(settinginfo()->edge_thickness);
  color = get_edge_color();
  glColor3f(color.redF(), color.greenF(), color.blueF());
  glDrawElements(GL_LINES, fig.edges.size(), GL_UNSIGNED_INT, fig.edges.data());
  if (settinginfo()->edges_type) {
    glDisable(GL_LINE_STIPPLE);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

void MyOpenGLRenderer::paintGL() {}

QColor MyOpenGLRenderer::get_color() {
  SettingInfo *info = settinginfo();
  return (info->background_color && !info->background_color->empty())
             ? QColor(QString::fromStdString(*info->background_color))
             : QColor();
}

QColor MyOpenGLRenderer::get_edge_color() {
  SettingInfo *info = settinginfo();
  return (info->edge_color && !info->edge_color->empty())
             ? QColor(QString::fromStdString(*info->edge_color))
             : QColor();
}

QColor MyOpenGLRenderer::get_points_color() {
  SettingInfo *info = settinginfo();
  return (info->vertex_color && !info->vertex_color->empty())
             ? QColor(QString::fromStdString(*info->vertex_color))
             : QColor();
}