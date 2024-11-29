#ifndef BG_OBJECTS_H
#define BG_OBJECTS_H

#include <stdlib.h>

#define F_HEIGHT 20
#define F_WIDTH 10
#define NEXT_HEIGHT 4
#define NEXT_WIDTH 4

#define GAME prms.activity != Terminate
#define NO_PAUSE (prms.activity != PAUSE)
#define TIME timer(&fall_timer, get_time_ms(), FALL_DELAY)

// информация об игре
typedef struct {
  int **field;
  int **next;
  int score;
  int highscore;
  int level;
  int speed;
  int pause;
} game_info_t;

// действия
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

// массивы-объекты
enum objects { INFO, F_SCREEN, LINE, HELPERS, COMBS, YOU_WIN, YOU_LOSE };
enum elem {
  ELEM1,
  ELEM2,
  ELEM3,
  ELEM4,
  ELEM5,
  ELEM6,
  ELEM7,
  ELEM8,
  ELEM9,
  ELEM10
};
enum help { HELP1, HELP2, HELP3, HELP4, HELP5 };
enum combinations {
  PAUSE1,
  PAUSE2,
  PAUSE3,
  SQUARE1,
  SQUARE2,
  NOPAUSE1,
  YOU1,
  YOU2,
  YOU3,
  YOU_LOSE1,
  YOU_LOSE2,
  YOU_LOSE3,
  YOU_WIN1,
  YOU_WIN2,
  YOU_WIN3,
};
enum info_word { HIGHSCORE, SCORE, LEVEL, SPEED, SPEED_UP, NEXT, YOUR_SCORE };

const char *bg_objects(int j, int i);

#endif