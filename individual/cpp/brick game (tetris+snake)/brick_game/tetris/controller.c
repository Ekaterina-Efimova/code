#include "controller.h"

GameInfo_t updateCurrentState() {
  params_t *t = get_tetris_game();
  update_next_field(t);
  while (t->tetris_state != EXIT_STATE) sigact(t);
  if (t->activity != Pause) {
    t->tetris_state = START;
    t->activity = Start;
  }
  return *(t->game_info);
}

void userInput(UserAction_t action, bool hold __attribute__((unused))) {
  params_t *t = get_tetris_game();

  if (action == Start)
    t->tetris_state = START;
  else if (action == Pause)
    t->tetris_state = PAUSE;
  else if (action == Left)
    t->tetris_state = MOVING;
  else if (action == Right)
    t->tetris_state = MOVING;
  else if (action == Up)
    t->tetris_state = MOVING;
  else if (action == Down)
    t->tetris_state = MOVING;
  else if (action == Terminate)
    t->tetris_state = GAMEOVER;
  else if (action == Action)
    t->tetris_state = MOVING;
  else
    t->tetris_state = -1;

  t->activity = action;
}

params_t *get_tetris_game() {
  static params_t t = {NULL, 0, 0, NULL, NULL, 0, 0, 0};
  if (!t.game_info) {
    tetris_malloc(&t);
    init_tetris(&t);
  }
  return &t;
}
