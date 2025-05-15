#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QColorDialog>
#include <QDateTime>
#include <QFileDialog>
#include <QGuiApplication>
#include <QMainWindow>
#include <QPixmap>
#include <QScreen>
#include <QScrollBar>
#include <QThread>
#include <QTimer>
#include <QWindow>
#include <filesystem>
#include <string>

#include "../controller/controller.h"
#include "QtGifImage/include/QtGifImage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_OpenFileButton_clicked();
  void on_SaveButton_clicked();
  void on_ScreenButton_clicked();
  void on_GifButton_clicked();
  void on_BackgroundColorButton_clicked();
  void on_VertexButton_clicked();
  void on_EdgesButton_clicked();
  void on_TransposeScrollBar_x_valueChanged(int value);
  void on_TransposeLineEdit_x_textChanged(const QString &text);
  void on_TransposeScrollBar_y_valueChanged(int value);
  void on_TransposeLineEdit_y_textChanged(const QString &text);
  void on_TransposeScrollBar_z_valueChanged(int value);
  void on_TransposeLineEdit_z_textChanged(const QString &text);
  void on_RotateScrollBar_x_valueChanged(int value);
  void on_RotateLineEdit_x_textChanged(const QString &text);
  void on_RotateScrollBar_y_valueChanged(int value);
  void on_RotateLineEdit_y_textChanged(const QString &text);
  void on_RotateScrollBar_z_valueChanged(int value);
  void on_RotateLineEdit_z_textChanged(const QString &text);
  void on_ScaleScrollBar_valueChanged(int value);
  void on_ScaleLineEdit_textChanged(const QString &text);
  void on_CancelEdgesButton_clicked(QAbstractButton *button);
  void on_ColorEdgesButton_clicked();
  void on_SizeEdgesScrollBar_valueChanged(int value);
  void on_EdgesLineEdit_textChanged(const QString &text);
  void on_CancelVertexButton_clicked(QAbstractButton *button);
  void on_ColorVertexButton_clicked();
  void on_SizeVertexScrollBar_valueChanged(int value);
  void on_VertexLineEdit_textChanged(const QString &text);
  void on_ParallelButton_clicked();
  void on_CenterButton_clicked();
  void new_frame();

 private:
  Ui::MainWindow *ui;
  Controller controller;

  //для временного хранения цвета
  std::unique_ptr<std::string> temp;

  //для отрисовки
  QOpenGLWidget *openGLWidget;

  //для гиф
  QTimer *t;
  QGifImage *gif;
  QString gif_file;

  QPixmap get_screen();
  void setupConnections();
  void updateOpenGLWidget();
  void updateInfoLabel();
  void update_edges();
  void update_vertex();
  void update_trans();
  void update_rotate();
  void update_scale();
};

//перечисления для номера окна
typedef enum { I_ONE, I_TWO, I_THREE } IndexType;

// перечисление для типа проекции
typedef enum { V_PARALLEL, V_CENTER } ProjectType;

}  // namespace s21
#endif  // MAINWINDOW_H
