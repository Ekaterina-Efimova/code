#pragma once

#include "../../common/bg_objects.h"
#include "snake_define.hpp"
#include "snake_fsm.hpp"

 // смена значения текущего состояния
  GameInfo_t updateCurrentState();
  // возврат пользовательского ввода
  void userInput(UserAction_t action, bool hold);

