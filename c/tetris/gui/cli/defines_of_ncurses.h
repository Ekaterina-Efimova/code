#ifndef DEFINE_OF_NCURSES_H
#define DEFINE_OF_NCURSES_H

#define WIN_INIT() \
  {                \
    initscr();     \
    noecho();      \
    curs_set(0);   \
  }

#define WIN_END()                                     \
  {                                                   \
    wattroff(brick_game_window, COLOR_PAIR(DEFAULT)); \
    delwin(brick_game_window);                        \
    endwin();                                         \
  }

#define PRINT()                                     \
  {                                                 \
    keypad(brick_game_window, TRUE);                \
    nodelay(brick_game_window, TRUE);               \
    start_color();                                  \
    init_pair(DEFAULT, COLOR_BLUE, COLOR_WHITE);    \
    init_pair(UNACTIVE, COLOR_YELLOW, COLOR_WHITE); \
    init_pair(WORDS, COLOR_MAGENTA, COLOR_WHITE);   \
  }

#endif