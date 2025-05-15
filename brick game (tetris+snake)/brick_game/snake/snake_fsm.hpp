#pragma once
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "../../common/bg_objects.h"
#include "snake_define.hpp"
#include "snake_model.hpp"

namespace s21 {
class Snake_fsm : private Snake_model  {
 private:
  // смена координат головы змейки
  void set_snake_head();

  // проверка таймера
  void check_timer();
  // поворот головы
  void move();
  // создание нового яблока
  void spawn();
  // пауза
  void pause();
  // рост змейки
  void growing();
  // выход из матрицы состояний
  void exit_state() { state = SNAKE_EXIT_STATE; };
  // присоединение яблока к змейке
  void conection();
  // конец из игры
  void game_over();
  // смещение змейк
  void shifting();
  // проверка
  void checking();
  // проверка на столкновение с границами
  bool check_die();

 public:
  static Snake_fsm *get_snake();
  // цикл игры
  void snake_game();

  // получение info
  GameInfo_t get_game_info() { return info; };
  // смена значения текущей активности
  void set_activity(int new_activity) { activity = new_activity; };
  // смена значения текущего состояния
  void set_state(UserAction_t action);
  // получение значения текущего состояния
  int get_state() { return state; };
  // получение значения текущей активности
  int get_activity() { return activity; };
  void set_hold(bool new_hold) { hold = new_hold; };
};
}  // namespace s21