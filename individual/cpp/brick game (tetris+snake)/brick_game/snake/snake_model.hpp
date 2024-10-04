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

namespace s21 {
class Snake_model {
 protected:
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> dis_width;
  std::uniform_int_distribution<> dis_height;
  mutable std::chrono::steady_clock::time_point timer;

  GameInfo_t info;
  std::vector<std::pair<int, int>> snake;
  std::vector<std::pair<int, int>> eat_apples;
  std::pair<int, int> apple;
  int activity;
  int state;
  int snake_length;
  int derect;
  bool gameover;
  bool hold;
  int conect;

  Snake_model();
  ~Snake_model();

  // выделение памяти для поля
  void malloc_field();
  // заполнение поля пустым значением
  void empty_field();
  // заполнение поля змейкой
  void put_snake();
  // инициализация следуюзщего поля
  void init_next_field();
  // инициализация яблока
  void init_apple();
  // проверка координат яблока, true - координаты совпали
  bool check_apple_coord();
  // инициализация информации о игре
  void init_game_info();
  // чтение лучшего счета
  void read_score();
  // запись лучшего счета
  void write_score();
    // смена поля
  void set_field();

 public:
  Snake_model(const Snake_model &) = delete;
  void operator=(const Snake_model &) = delete;
};
}  // namespace s21