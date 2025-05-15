#ifndef DESKTOP_H_
#define DESKTOP_H_

#include <QDebug>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "../../common/bg_objects.h"

#if defined TETRIS
#include "../../brick_game/tetris/controller.h"
#else
#include "../../brick_game/snake/controller.h"
#endif

#define SIZE_DOT 30

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

  // номера цветов
  enum color { GREY, RED, GREEN, YELLOW, ORANGE };
  // цвета
  const QColor colors[8] = {
      QColor(125, 125, 125),  // серый
      QColor(255, 0, 0),      // красный
      QColor(103, 250, 0),    // зеленый
      QColor(250, 235, 5),    // желтый
      QColor(250, 200, 5),    // оранжевый
  };
  enum game { NONE, SNAKE, TETRIS };

 protected:
  void keyPressEvent(QKeyEvent *) override;
  void paintEvent(QPaintEvent *event) override;

 private:
  QTimer *timer;
  Ui::View *ui;
  UserAction_t action;
  GameInfo_t info;

  void update();
  void render();
  void start_window(QLabel *p_label);
  void pause_window(QLabel *p_label);
};

}  // namespace s21

#endif
