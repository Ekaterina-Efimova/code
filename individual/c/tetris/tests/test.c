#include <check.h>
#include <math.h>

#include "../brick_game/bg_objects.h"
#include "../brick_game/helper.h"
#include "../brick_game/tetris/tetris_backend.h"
#include "../brick_game/tetris/tetris_check.h"
#include "../brick_game/tetris/tetris_matrix.h"
#include "../brick_game/tetris/tetris_objects.h"

START_TEST(init) {
  params_t prms;
  tetris_malloc(&prms);
  init_tetris(&prms);
  int highscore;
  read_highscore(FILE_SCORE, &highscore);

  if (prms.game_info->field)
    for (int i = 0; i < F_HEIGHT; ++i)
      for (int j = 0; j < F_WIDTH; ++j)
        ck_assert(prms.game_info->field[i][j] == 0);
  if (prms.game_info->next)
    for (int i = 0; i < NEXT_HEIGHT; ++i)
      for (int j = 0; j < NEXT_WIDTH; ++j)
        ck_assert(prms.game_info->next[i][j] == 0);

  for (int i = 0; i < 4; ++i) {
    if (prms.tetramino->type == I) {
      if (prms.tetramino->state == FIRST || prms.tetramino->state == THIRD) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == 0);
        ck_assert(prms.tetramino->tetramino_state[i][X] == i + 3);
      } else if (prms.tetramino->state == SECOND ||
                 prms.tetramino->state == FOURTH) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == i);
        ck_assert(prms.tetramino->tetramino_state[i][X] == 3);
      }

    } else if (prms.tetramino->type == J) {
      if (prms.tetramino->state == FIRST) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i < 3 ? 0 : 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i < 3 ? i + 3 : 5));
      } else if (prms.tetramino->state == SECOND) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i < 3 ? i : 2));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i < 3 ? 4 : 3));
      } else if (prms.tetramino->state == THIRD) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i == 0 ? 0 : 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i < 2 ? 3 : i + 2));
      } else if (prms.tetramino->state == FOURTH) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i < 2 ? 0 : i - 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i == 0 ? 4 : 3));
      }

    } else if (prms.tetramino->type == L) {
      if (prms.tetramino->state == FIRST) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i == 0 ? 1 : 0));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i < 2 ? 4 : i + 3));
      } else if (prms.tetramino->state == SECOND) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i < 2 ? 0 : i - 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i == 0 ? 5 : 6));
      } else if (prms.tetramino->state == THIRD) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i == 0 ? 0 : 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i < 2    ? 6
                                                            : i == 2 ? 5
                                                                     : 4));
      } else if (prms.tetramino->state == FOURTH) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i == 3 ? 2 : i));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i == 3 ? 5 : 4));
      }

    } else if (prms.tetramino->type == O) {
      ck_assert(prms.tetramino->tetramino_state[i][Y] == (i < 2 ? 0 : 1));
      ck_assert(prms.tetramino->tetramino_state[i][X] ==
                ((i % 2) == 0 ? 4 : 5));

    } else if (prms.tetramino->type == S) {
      if (prms.tetramino->state == FIRST || prms.tetramino->state == THIRD) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i < 2 ? 0 : 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i < 2    ? i + 4
                                                            : i == 3 ? 4
                                                                     : 3));
      } else if (prms.tetramino->state == SECOND ||
                 prms.tetramino->state == FOURTH) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i == 0   ? 0
                                                            : i == 3 ? 2
                                                                     : 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i < 2 ? 3 : 4));
      }

    } else if (prms.tetramino->type == Z) {
      if (prms.tetramino->state == FIRST || prms.tetramino->state == THIRD) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i < 2 ? 0 : 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i == 0   ? 3
                                                            : i == 3 ? 5
                                                                     : 4));
      } else if (prms.tetramino->state == SECOND ||
                 prms.tetramino->state == FOURTH) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i == 0   ? 0
                                                            : i == 3 ? 2
                                                                     : 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] ==
                  ((i % 2) == 0 ? 5 : 4));
      }

    } else if (prms.tetramino->type == T) {
      if (prms.tetramino->state == FIRST) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i == 3 ? 1 : 0));
        ck_assert(prms.tetramino->tetramino_state[i][X] ==
                  (i == 3 ? 4 : i + 3));
      } else if (prms.tetramino->state == SECOND) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i < 2 ? i : i - 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i == 1 ? 3 : 4));
      } else if (prms.tetramino->state == THIRD) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] == (i == 0 ? 0 : 1));
        ck_assert(prms.tetramino->tetramino_state[i][X] ==
                  (i < 2 ? 4 - i : i + 2));
      } else if (prms.tetramino->state == FOURTH) {
        ck_assert(prms.tetramino->tetramino_state[i][Y] ==
                  (i < 2 ? i + 1 : i - 2));
        ck_assert(prms.tetramino->tetramino_state[i][X] == (i == 3 ? 5 : 4));
      }
    }
  }
  ck_assert(prms.game_info->highscore == highscore);
  ck_assert(prms.game_info->level == 1);
  ck_assert(prms.game_info->pause == 1);
  ck_assert(prms.game_info->score == 0);
  ck_assert(prms.game_info->speed == 1);
  ck_assert(prms.tetris_state == PAUSE);
  ck_assert(prms.activity == Pause);
  ck_assert(prms.line_counter == 0);
  // ck_assert(prms.flag == 0);

  tetris_free(&prms);
}
END_TEST

START_TEST(free_1) {
  params_t prms;
  tetris_malloc(&prms);

  tetris_free(&prms);

  ck_assert(prms.tetramino == NULL);
  ck_assert(prms.next_tetr == NULL);
  ck_assert(prms.game_info == NULL);
}
END_TEST

START_TEST(service_1) {
  int highscore, chec, tmp = 0;
  read_highscore(FILE_SCORE, &highscore);
  write_highscore(FILE_SCORE, &tmp);
  read_highscore(FILE_SCORE, &chec);
  write_highscore(FILE_SCORE, &highscore);

  ck_assert(tmp == chec);
}
END_TEST

START_TEST(service_2) {
  long long prev_time = get_time_ms();
  ck_assert(timer(&prev_time, get_time_ms(), 0));
  ck_assert(!timer(&prev_time, get_time_ms(), 1000));
}
END_TEST

START_TEST(service_3) {
  game_info_t game = {0};
  game.highscore = 0;
  game.score = 300;
  int chec = 300;
  int tmp = 0;

  result(&game);
  read_highscore(FILE_SCORE, &tmp);

  ck_assert(tmp == chec);
}

START_TEST(fall) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  for (int i = 0; i < 4; ++i) ++prms.tetramino->tetramino_state[i][Y];

  ck_assert(!check_fallen(prms.game_info->field, prms.tetramino));

  tetris_free(&prms);
}
END_TEST

START_TEST(loss) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);
  prms.game_info->field[0][3] = 2;

  ck_assert(check_loss(prms.game_info->field));

  tetris_free(&prms);
}
END_TEST

START_TEST(intersection) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  ck_assert(!check_intersection(prms.game_info->field, prms.tetramino));

  tetris_free(&prms);
}
END_TEST

START_TEST(right) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  ck_assert(!check_frame_rigth(prms.tetramino));

  tetris_free(&prms);
}
END_TEST

START_TEST(left) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  ck_assert(!check_frame_left(prms.tetramino));

  tetris_free(&prms);
}
END_TEST

START_TEST(check_distroy_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  ck_assert(!check_distroy(prms.game_info->field, 19));

  tetris_free(&prms);
}
END_TEST

START_TEST(update_field_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  prms.tetramino->type = I;
  prms.tetramino->state = FIRST;
  prms.tetramino->tetramino_state[0][X] = 3;
  prms.tetramino->tetramino_state[0][Y] = 0;
  prms.tetramino->tetramino_state[1][X] = 4;
  prms.tetramino->tetramino_state[1][Y] = 0;
  prms.tetramino->tetramino_state[2][X] = 5;
  prms.tetramino->tetramino_state[2][Y] = 0;
  prms.tetramino->tetramino_state[3][X] = 6;
  prms.tetramino->tetramino_state[3][Y] = 0;

  update_field(&prms);

  ck_assert(prms.game_info->field[0][3] == 1);
  ck_assert(prms.game_info->field[0][4] == 1);
  ck_assert(prms.game_info->field[0][5] == 1);
  ck_assert(prms.game_info->field[0][6] == 1);

  tetris_free(&prms);
}
END_TEST

START_TEST(update_figure_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  tetramino_position temp = {0};

  BLOCKS {
    temp.tetramino_state[i][X] = prms.next_tetr->tetramino_state[i][X];
    temp.tetramino_state[i][Y] = prms.next_tetr->tetramino_state[i][Y];
  }

  update_figure(prms.tetramino, prms.next_tetr);

  BLOCKS {
    ck_assert(temp.tetramino_state[i][X] ==
              prms.tetramino->tetramino_state[i][X]);
    ck_assert(
        temp.tetramino_state[i][Y == prms.tetramino->tetramino_state[i][Y]]);
  }

  tetris_free(&prms);
}
END_TEST

START_TEST(spawn_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  params_t temp = {0};
  tetris_malloc(&temp);
  init_tetris(&temp);

  temp.next_tetr->type = prms.next_tetr->type;
  temp.next_tetr->state = prms.next_tetr->state;
  tetraminoes(temp.next_tetr->type, temp.next_tetr->state,
              temp.next_tetr->tetramino_state);

  temp.tetramino->type = prms.next_tetr->type;
  temp.tetramino->state = prms.next_tetr->state;
  tetraminoes(temp.next_tetr->type, temp.next_tetr->state,
              temp.tetramino->tetramino_state);

  add_figure(temp.game_info->field, temp.tetramino, 1);
  update_next_field(&temp);
  temp.tetris_state = CHECKING;

  spawn(&prms);

  BLOCKS {
    ck_assert(temp.tetramino->tetramino_state[i][X] ==
              prms.tetramino->tetramino_state[i][X]);
    ck_assert(temp.tetramino->tetramino_state[i][Y] ==
              prms.tetramino->tetramino_state[i][Y]);
  }

  FIELD ck_assert(temp.game_info->field[i][j] == prms.game_info->field[i][j]);

  ck_assert(prms.tetris_state == temp.tetris_state);

  tetris_free(&temp);
  tetris_free(&prms);
}
END_TEST

START_TEST(shifting_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  params_t temp = {0};
  tetris_malloc(&temp);

  init_tetris(&temp);
  temp.tetramino->type = prms.tetramino->type;
  temp.tetramino->state = prms.tetramino->state;
  tetraminoes(temp.tetramino->type, temp.tetramino->state,
              temp.tetramino->tetramino_state);

  add_figure(temp.game_info->field, temp.tetramino, 1);
  BLOCKS temp.Y_FIGURE++;
  temp.tetramino->count_down++;
  update_field(&temp);
  temp.tetris_state = CHECKING;

  shifting(&prms);

  BLOCKS {
    ck_assert(temp.tetramino->tetramino_state[i][X] ==
              prms.tetramino->tetramino_state[i][X]);
    ck_assert(temp.tetramino->tetramino_state[i][Y] ==
              prms.tetramino->tetramino_state[i][Y]);
  }

  ck_assert(prms.tetris_state == temp.tetris_state);
  ck_assert(prms.tetramino->count_down == temp.tetramino->count_down);

  tetris_free(&temp);
  tetris_free(&prms);
}
END_TEST

START_TEST(pause_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  pauses(&prms);

  ck_assert(prms.game_info->pause == 1);
  ck_assert(prms.tetris_state == EXIT_STATE);

  tetris_free(&prms);
}
END_TEST

START_TEST(moveleft_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  params_t temp = {0};
  tetris_malloc(&temp);

  init_tetris(&temp);
  temp.tetramino->type = prms.tetramino->type;
  temp.tetramino->state = prms.tetramino->state;
  tetraminoes(temp.tetramino->type, temp.tetramino->state,
              temp.tetramino->tetramino_state);
  add_figure(temp.game_info->field, temp.tetramino, 1);
  BLOCKS temp.X_FIGURE--;
  temp.tetramino->count_width--;
  update_field(&temp);
  temp.tetris_state = CHECKING;

  moveleft(&prms);

  BLOCKS {
    ck_assert(temp.tetramino->tetramino_state[i][X] ==
              prms.tetramino->tetramino_state[i][X]);
    ck_assert(temp.tetramino->tetramino_state[i][Y] ==
              prms.tetramino->tetramino_state[i][Y]);
  }

  ck_assert(prms.tetris_state == temp.tetris_state);
  ck_assert(prms.tetramino->count_width == temp.tetramino->count_width);

  tetris_free(&temp);
  tetris_free(&prms);
}
END_TEST

START_TEST(moveright_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  params_t temp = {0};
  tetris_malloc(&temp);

  init_tetris(&temp);
  temp.tetramino->type = prms.tetramino->type;
  temp.tetramino->state = prms.tetramino->state;
  tetraminoes(temp.tetramino->type, temp.tetramino->state,
              temp.tetramino->tetramino_state);
  add_figure(temp.game_info->field, temp.tetramino, 1);
  BLOCKS temp.X_FIGURE++;
  temp.tetramino->count_width++;
  update_field(&temp);
  temp.tetris_state = CHECKING;

  moveright(&prms);

  BLOCKS {
    ck_assert(temp.tetramino->tetramino_state[i][X] ==
              prms.tetramino->tetramino_state[i][X]);
    ck_assert(temp.tetramino->tetramino_state[i][Y] ==
              prms.tetramino->tetramino_state[i][Y]);
  }

  ck_assert(prms.tetris_state == temp.tetris_state);
  ck_assert(prms.tetramino->count_width == temp.tetramino->count_width);

  tetris_free(&temp);
  tetris_free(&prms);
}
END_TEST

START_TEST(rotate_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  params_t temp = {0};
  tetris_malloc(&temp);

  init_tetris(&temp);
  temp.tetramino->type = prms.tetramino->type;
  temp.tetramino->state = prms.tetramino->state;
  tetraminoes(temp.tetramino->type, temp.tetramino->state,
              temp.tetramino->tetramino_state);
  temp.tetramino->state++;
  if (temp.tetramino->state >= 4) temp.tetramino->state %= 4;
  tetraminoes(temp.tetramino->type, temp.tetramino->state,
              temp.tetramino->tetramino_state);
  update_field(&temp);
  temp.tetris_state = CHECKING;

  rotate(&prms);

  BLOCKS {
    ck_assert(temp.tetramino->tetramino_state[i][X] ==
              prms.tetramino->tetramino_state[i][X]);
    ck_assert(temp.tetramino->tetramino_state[i][Y] ==
              prms.tetramino->tetramino_state[i][Y]);
  }

  ck_assert(prms.tetris_state == temp.tetris_state);

  tetris_free(&temp);
  tetris_free(&prms);
}
END_TEST

START_TEST(distroy_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);
  for (int i = 0; i < F_WIDTH; i++) prms.game_info->field[19][i] = CONSTANT;

  distroy(&prms);

  ck_assert(prms.game_info->score == 100);
  ck_assert(prms.game_info->level == 1);
  ck_assert(prms.game_info->speed == 1);
  ck_assert(prms.tetris_state == SPAWN);

  tetris_free(&prms);
}
END_TEST

START_TEST(conection_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  params_t temp = {0};
  tetris_malloc(&temp);

  init_tetris(&temp);
  change_tetramino(temp.tetramino, prms.tetramino);

  BLOCKS temp.game_info->field[temp.Y_FIGURE][temp.X_FIGURE] = CONSTANT;

  conection(&prms);

  ck_assert(prms.tetris_state == CHECKING);
  ck_assert(prms.flag == CONECTION);

  tetris_free(&temp);
  tetris_free(&prms);
}
END_TEST

START_TEST(exitstate_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  exitstate(&prms);

  ck_assert(prms.tetris_state == EXIT_STATE);

  tetris_free(&prms);
}
END_TEST

START_TEST(gameover_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  gameover(&prms);

  ck_assert(prms.tetris_state == EXIT_STATE);
  ck_assert(prms.flag == GAMEOVER);

  tetris_free(&prms);
}
END_TEST

START_TEST(checking_1) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  spawn(&prms);
  check(&prms);

  ck_assert(prms.tetris_state == EXIT_STATE);
  ck_assert(prms.activity == Start);
  ck_assert(prms.flag == SPAWN);

  tetris_free(&prms);
}

START_TEST(checking_2) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);
  prms.tetramino->type = 1;
  prms.tetramino->state = 0;
  tetraminoes(prms.tetramino->type, prms.tetramino->state,
              prms.tetramino->tetramino_state);

  BLOCKS prms.Y_FIGURE += 18;
  prms.flag = SPAWN;
  update_field(&prms);

  check(&prms);

  ck_assert(prms.tetris_state == EXIT_STATE);

  tetris_free(&prms);
}

START_TEST(checking_3) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);
  prms.tetramino->type = 1;
  prms.tetramino->state = 0;
  tetraminoes(prms.tetramino->type, prms.tetramino->state,
              prms.tetramino->tetramino_state);

  prms.flag = CONECTION;
  update_field(&prms);

  BLOCKS prms.game_info->field[prms.Y_FIGURE][prms.X_FIGURE] = CONSTANT;

  check(&prms);

  ck_assert(prms.tetris_state == GAMEOVER);

  tetris_free(&prms);
}

START_TEST(checking_4) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);
  prms.tetramino->type = 1;
  prms.tetramino->state = 0;
  tetraminoes(prms.tetramino->type, prms.tetramino->state,
              prms.tetramino->tetramino_state);
  BLOCKS prms.Y_FIGURE += 18;
  prms.flag = SHIFTING;
  update_field(&prms);

  check(&prms);

  ck_assert(prms.tetris_state == CONECTION);

  tetris_free(&prms);
}
START_TEST(checking_5) {
  params_t prms = {0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  BLOCKS prms.Y_FIGURE += 19;
  prms.flag = CONECTION;
  update_field(&prms);

  check(&prms);

  ck_assert(prms.tetris_state == DISTROY);

  tetris_free(&prms);
}

START_TEST(bg_objects_1) {
  const char *ch1 = bg_objects(INFO, 0);
  const char *ch2 = bg_objects(F_SCREEN, 1);
  const char *ch3 = bg_objects(LINE, 2);
  const char *ch4 = bg_objects(HELPERS, 3);
  const char *ch5 = bg_objects(COMBS, 4);
  const char *ch6 = bg_objects(YOU_WIN, 5);
  const char *ch7 = bg_objects(YOU_LOSE, 6);

  ck_assert(ch1 != NULL);
  ck_assert(ch2 != NULL);
  ck_assert(ch3 != NULL);
  ck_assert(ch4 != NULL);
  ck_assert(ch5 != NULL);
  ck_assert(ch6 != NULL);
  ck_assert(ch7 != NULL);
}
END_TEST

START_TEST(sigact_1) {
  params_t prms = {0};
  tetris_malloc(&prms);
  prms.tetris_state = EXIT_STATE;

  sigact(&prms);
  ck_assert(prms.tetris_state == EXIT_STATE);

  tetris_free(&prms);
}
END_TEST
Suite *sigact_cases(void) {
  Suite *c = suite_create("sigact_cases");
  TCase *tc = tcase_create("sigact_tc");

  tcase_add_test(tc, sigact_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *bg_objects_cases(void) {
  Suite *c = suite_create("bg_objects_cases");
  TCase *tc = tcase_create("bg_objects_tc");

  tcase_add_test(tc, bg_objects_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *checking_cases(void) {
  Suite *c = suite_create("checking_cases");
  TCase *tc = tcase_create("checking_tc");

  tcase_add_test(tc, checking_1);
  tcase_add_test(tc, checking_2);
  tcase_add_test(tc, checking_3);
  tcase_add_test(tc, checking_4);
  tcase_add_test(tc, checking_5);

  suite_add_tcase(c, tc);

  return c;
}
Suite *gameover_cases(void) {
  Suite *c = suite_create("gameover_cases");
  TCase *tc = tcase_create("gameover_tc");

  tcase_add_test(tc, gameover_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *exitstate_cases(void) {
  Suite *c = suite_create("exitstate_cases");
  TCase *tc = tcase_create("exitstate_tc");

  tcase_add_test(tc, exitstate_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *conection_cases(void) {
  Suite *c = suite_create("conection_cases");
  TCase *tc = tcase_create("conection_tc");

  tcase_add_test(tc, conection_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *distroy_cases(void) {
  Suite *c = suite_create("distroy_cases");
  TCase *tc = tcase_create("distroy_tc");

  tcase_add_test(tc, distroy_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *rotate_cases(void) {
  Suite *c = suite_create("rotate_cases");
  TCase *tc = tcase_create("rotate_tc");

  tcase_add_test(tc, rotate_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *moveright_cases(void) {
  Suite *c = suite_create("moveright_cases");
  TCase *tc = tcase_create("moveright_tc");

  tcase_add_test(tc, moveright_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *moveleft_cases(void) {
  Suite *c = suite_create("moveleft_cases");
  TCase *tc = tcase_create("moveleft_tc");

  tcase_add_test(tc, moveleft_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *pause_cases(void) {
  Suite *c = suite_create("pause_cases");
  TCase *tc = tcase_create("pause_tc");
  tcase_add_test(tc, pause_1);
  suite_add_tcase(c, tc);
  return c;
}

Suite *shifting_cases(void) {
  Suite *c = suite_create("shifting_cases");
  TCase *tc = tcase_create("shifting_tc");

  tcase_add_test(tc, shifting_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *spawn_cases(void) {
  Suite *c = suite_create("spawn_cases");
  TCase *tc = tcase_create("spawn_tc");

  tcase_add_test(tc, spawn_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *update_figure_cases(void) {
  Suite *c = suite_create("update_figure_cases");
  TCase *tc = tcase_create("update_figure_tc");

  tcase_add_test(tc, update_figure_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *update_field_cases(void) {
  Suite *c = suite_create("update_field_cases");
  TCase *tc = tcase_create("update_field_tc");

  tcase_add_test(tc, update_field_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *check_distroy_cases(void) {
  Suite *c = suite_create("check_distroy_cases");
  TCase *tc = tcase_create("check_distroy_tc");

  tcase_add_test(tc, check_distroy_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *check_right_cases(void) {
  Suite *c = suite_create("check_right_cases");
  TCase *tc = tcase_create("check_right_tc");

  tcase_add_test(tc, right);

  suite_add_tcase(c, tc);

  return c;
}
Suite *check_left_cases(void) {
  Suite *c = suite_create("check_left_cases");
  TCase *tc = tcase_create("check_left_tc");

  tcase_add_test(tc, left);

  suite_add_tcase(c, tc);

  return c;
}
Suite *check_intersection_cases(void) {
  Suite *c = suite_create("check_intersection_cases");
  TCase *tc = tcase_create("check_intersection_tc");

  tcase_add_test(tc, intersection);

  suite_add_tcase(c, tc);

  return c;
}
Suite *check_loss_cases(void) {
  Suite *c = suite_create("check_loss_cases");
  TCase *tc = tcase_create("check_loss_tc");

  tcase_add_test(tc, loss);

  suite_add_tcase(c, tc);

  return c;
}
Suite *fall_cases(void) {
  Suite *c = suite_create("fall_cases");
  TCase *tc = tcase_create("fall_tc");

  tcase_add_test(tc, fall);

  suite_add_tcase(c, tc);

  return c;
}
Suite *service_cases(void) {
  Suite *c = suite_create("service_cases");
  TCase *tc = tcase_create("service_tc");

  tcase_add_test(tc, service_1);
  tcase_add_test(tc, service_2);
  tcase_add_test(tc, service_3);

  suite_add_tcase(c, tc);

  return c;
}
Suite *free_cases(void) {
  Suite *c = suite_create("free_cases");
  TCase *tc = tcase_create("free_tc");

  tcase_add_test(tc, free_1);

  suite_add_tcase(c, tc);

  return c;
}
Suite *init_cases(void) {
  Suite *c = suite_create("init_cases");
  TCase *tc = tcase_create("init_tc");

  tcase_add_test(tc, init);

  suite_add_tcase(c, tc);

  return c;
}

int main() {
  srand(time(NULL));
  int number_failed;
  SRunner *sr;

  sr = srunner_create(NULL);

  srunner_add_suite(sr, init_cases());
  srunner_add_suite(sr, free_cases());
  srunner_add_suite(sr, service_cases());
  srunner_add_suite(sr, fall_cases());
  srunner_add_suite(sr, check_loss_cases());
  srunner_add_suite(sr, check_intersection_cases());
  srunner_add_suite(sr, check_right_cases());
  srunner_add_suite(sr, check_left_cases());
  srunner_add_suite(sr, check_distroy_cases());
  srunner_add_suite(sr, update_field_cases());
  srunner_add_suite(sr, update_figure_cases());
  srunner_add_suite(sr, spawn_cases());
  srunner_add_suite(sr, shifting_cases());
  srunner_add_suite(sr, pause_cases());
  srunner_add_suite(sr, moveleft_cases());
  srunner_add_suite(sr, moveright_cases());
  srunner_add_suite(sr, rotate_cases());
  srunner_add_suite(sr, distroy_cases());
  srunner_add_suite(sr, conection_cases());
  srunner_add_suite(sr, exitstate_cases());
  srunner_add_suite(sr, checking_cases());
  srunner_add_suite(sr, gameover_cases());
  srunner_add_suite(sr, bg_objects_cases());
  srunner_add_suite(sr, sigact_cases());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}