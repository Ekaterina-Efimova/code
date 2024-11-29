#ifndef HELPER_H
#define HELPER_H

#include <ncursesw/curses.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "bg_objects.h"
#include "tetris/tetris_objects.h"

void read_highscore(char *filename, int *highscore);
void write_highscore(char *filename, int *highscore);

long long get_time_ms();
int timer(long long *prev_time, long long curr_time, int delay);

void result(game_info_t *game_info);

#endif