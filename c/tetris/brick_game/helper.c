#include "helper.h"

void read_highscore(char *filename, int *highscore) {
  FILE *file = fopen(filename, "r+");
  if (file) {
    fscanf(file, "%d", highscore);
    fclose(file);
  }
}

void write_highscore(char *filename, int *highscore) {
  FILE *file = fopen(filename, "w+");
  if (file) {
    fprintf(file, "%d", *highscore);
    fclose(file);
  }
}

long long get_time_ms() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int timer(long long *prev_time, long long curr_time, int delay) {
  int res = 0;
  if (curr_time - *prev_time >= delay) {
    *prev_time = curr_time;
    res = 1;
  }
  return res;
}

void result(game_info_t *game_info) {
  if (game_info->score > game_info->highscore) {
    write_highscore(FILE_SCORE, &game_info->score);
    game_info->highscore = game_info->score;
  }
}
