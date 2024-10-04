#include <locale.h>
#include <math.h>
#include <stdlib.h>

#include "../gui/cli/interface.h"

int main() {
  setlocale(LC_ALL, "");
  WIN_INIT();
  WINDOW *brick_game_window = init_ncurses();
  print_display(brick_game_window);
  bg_game(brick_game_window);
  WIN_END();
  return 0;
}