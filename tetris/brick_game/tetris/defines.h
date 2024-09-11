#ifndef DEFINES_H
#define DEFINES_H

#define GET_USER_INPUT getch()

#define FILE_SCORE "brick_game/tetris/score/tetris_highscore.txt"

// максимальный уровень
#define LEVEL_CNT 10
#define LEVEL_UP_SCORE 600
#define MAX_SCORE 6000

// циклы
#define BLOCKS for (int i = 0; i < 4; i++)
#define CHECK for (int i = 0; i < 4 && !res; i++)
#define FIELD                        \
  for (int i = 0; i < F_HEIGHT; i++) \
    for (int j = 0; j < F_WIDTH; j++)

// координаты фигуры
#define X_FIGURE tetramino->tetramino_state[i][X]
#define Y_FIGURE tetramino->tetramino_state[i][Y]

// скорость
#define FALL_DELAY 1000 / pow(1.25, prms.game_info->level)
#endif