#include <locale.h>
#include <math.h>

#include "../gui/cli/interface.h"
#include "tetris/tetris_matrix.h"
#include "tetris/tetris_objects.h"

int tetris(WINDOW *brick_game_window) {
  srand(time(NULL));

  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  update_next_field(&prms);
  update_display(brick_game_window, prms.game_info);

  while (prms.activity != Start && prms.activity != Terminate)
    user_input(brick_game_window, &prms.activity, &prms.tetris_state);

  long long fall_timer = get_time_ms();
  spawn(&prms);

  while (GAME) {
    user_input(brick_game_window, &prms.activity, &prms.tetris_state);

    if (NO_PAUSE) {
      prms.game_info->pause = 0;
      if (TIME) prms.tetris_state = SHIFTING;
    } else {
      prms.game_info->pause = 1;
      prms.tetris_state = PAUSE;
    }

    while (prms.tetris_state != EXIT_STATE) sigact(&prms);

    result(prms.game_info);
    update_display(brick_game_window, prms.game_info);

    if (prms.flag == GAMEOVER) {
      while (prms.activity != Terminate) {
        print_result(brick_game_window, prms.game_info);
        user_input(brick_game_window, &prms.activity, &prms.tetris_state);
      }
    }
  }

  tetris_free(&prms);
  return 0;
}

int main() {
  setlocale(LC_ALL, "");
  WIN_INIT();

  WINDOW *brick_game_window = init_ncurses();

  print_display(brick_game_window);
  tetris(brick_game_window);

  WIN_END();

  return 0;
}