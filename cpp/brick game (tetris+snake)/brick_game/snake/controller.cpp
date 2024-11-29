#include "controller.h"

using namespace s21;

GameInfo_t updateCurrentState() {
  while (Snake_fsm::get_snake()->get_state() != SNAKE_EXIT_STATE)
    Snake_fsm::get_snake()->snake_game();
  if (Snake_fsm::get_snake()->get_activity() != Pause) {
    Snake_fsm::get_snake()->set_activity(Action);
    Snake_fsm::get_snake()->set_state(
        (UserAction_t)Snake_fsm::get_snake()->get_activity());
  }

  return Snake_fsm::get_snake()->get_game_info();
}

void userInput(UserAction_t action, bool hold) {
  Snake_fsm::get_snake()->set_activity(action);
  Snake_fsm::get_snake()->set_hold(hold);
  Snake_fsm::get_snake()->set_state(action);
}