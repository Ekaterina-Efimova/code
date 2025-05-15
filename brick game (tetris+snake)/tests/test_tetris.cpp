#include "test.hpp"

TEST(TetrisTest, Init) {
  params_t prms;
  tetris_malloc(&prms);
  init_tetris(&prms);
  int highscore;
  read_highscore(FILE_SCORE, &highscore);

  if (prms.game_info->field) {
    for (int i = 0; i < F_HEIGHT; ++i)
      for (int j = 0; j < F_WIDTH; ++j)
        EXPECT_EQ(prms.game_info->field[i][j], 0);
  }

  if (prms.game_info->next) {
    for (int i = 0; i < NEXT_HEIGHT; ++i)
      for (int j = 0; j < NEXT_WIDTH; ++j)
        EXPECT_EQ(prms.game_info->next[i][j], 0);
  }

  for (int i = 0; i < 4; ++i) {
    if (prms.tetramino->type == I) {
      if (prms.tetramino->state == FIRST || prms.tetramino->state == THIRD) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], 0);
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], i + 3);
      } else if (prms.tetramino->state == SECOND ||
                 prms.tetramino->state == FOURTH) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], i);
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], 3);
      }
    } else if (prms.tetramino->type == J) {
      if (prms.tetramino->state == FIRST) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i < 3 ? 0 : 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i < 3 ? i + 3 : 5));
      } else if (prms.tetramino->state == SECOND) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i < 3 ? i : 2));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i < 3 ? 4 : 3));
      } else if (prms.tetramino->state == THIRD) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i == 0 ? 0 : 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i < 2 ? 3 : i + 2));
      } else if (prms.tetramino->state == FOURTH) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i < 2 ? 0 : i - 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i == 0 ? 4 : 3));
      }
    } else if (prms.tetramino->type == L) {
      if (prms.tetramino->state == FIRST) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i == 0 ? 1 : 0));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i < 2 ? 4 : i + 3));
      } else if (prms.tetramino->state == SECOND) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i < 2 ? 0 : i - 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i == 0 ? 5 : 6));
      } else if (prms.tetramino->state == THIRD) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i == 0 ? 0 : 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i < 2    ? 6
                                                          : i == 2 ? 5
                                                                   : 4));
      } else if (prms.tetramino->state == FOURTH) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i == 3 ? 2 : i));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i == 3 ? 5 : 4));
      }

    } else if (prms.tetramino->type == O) {
      EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i < 2 ? 0 : 1));
      EXPECT_EQ(prms.tetramino->tetramino_state[i][X], ((i % 2) == 0 ? 4 : 5));
    } else if (prms.tetramino->type == S) {
      if (prms.tetramino->state == FIRST || prms.tetramino->state == THIRD) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i < 2 ? 0 : 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i < 2    ? i + 4
                                                          : i == 3 ? 4
                                                                   : 3));
      } else if (prms.tetramino->state == SECOND ||
                 prms.tetramino->state == FOURTH) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i == 0   ? 0
                                                          : i == 3 ? 2
                                                                   : 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i < 2 ? 3 : 4));
      }
    } else if (prms.tetramino->type == Z) {
      if (prms.tetramino->state == FIRST || prms.tetramino->state == THIRD) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i < 2 ? 0 : 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i == 0   ? 3
                                                          : i == 3 ? 5
                                                                   : 4));
      } else if (prms.tetramino->state == SECOND ||
                 prms.tetramino->state == FOURTH) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i == 0   ? 0
                                                          : i == 3 ? 2
                                                                   : 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X],
                  ((i % 2) == 0 ? 5 : 4));
      }
    } else if (prms.tetramino->type == T) {
      if (prms.tetramino->state == FIRST) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i == 3 ? 1 : 0));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i == 3 ? 4 : i + 3));
      } else if (prms.tetramino->state == SECOND) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i < 2 ? i : i - 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i == 1 ? 3 : 4));
      } else if (prms.tetramino->state == THIRD) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y], (i == 0 ? 0 : 1));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X],
                  (i < 2 ? 4 - i : i + 2));
      } else if (prms.tetramino->state == FOURTH) {
        EXPECT_EQ(prms.tetramino->tetramino_state[i][Y],
                  (i < 2 ? i + 1 : i - 2));
        EXPECT_EQ(prms.tetramino->tetramino_state[i][X], (i == 3 ? 5 : 4));
      }
    }
  }

  EXPECT_EQ(prms.game_info->highscore, highscore);
  EXPECT_EQ(prms.game_info->level, 1);
  EXPECT_EQ(prms.game_info->pause, 1);
  EXPECT_EQ(prms.game_info->score, 0);
  EXPECT_EQ(prms.game_info->speed, 1);
  EXPECT_EQ(prms.tetris_state, PAUSE);
  EXPECT_EQ(prms.activity, Pause);
  EXPECT_EQ(prms.line_counter, 0);

  tetris_free(&prms);
}

TEST(FreeTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);

  tetris_free(&prms);

  ASSERT_TRUE(prms.tetramino == NULL);
  ASSERT_TRUE(prms.next_tetr == NULL);
  ASSERT_TRUE(prms.game_info == NULL);
}

TEST(ServiceTest, TestCase1) {
  int highscore, chec, tmp = 0;
  read_highscore(FILE_SCORE, &highscore);
  write_highscore(FILE_SCORE, &tmp);
  read_highscore(FILE_SCORE, &chec);
  write_highscore(FILE_SCORE, &highscore);

  ASSERT_EQ(tmp, chec);
}

TEST(ServiceTest, TestCase2) {
  GameInfo_t game = {NULL, NULL, 0, 0, 0, 0, 0};
  game.highscore = 0;
  game.score = 300;
  int chec = 300;
  int tmp = 0;

  result(&game, FILE_SCORE);
  read_highscore(FILE_SCORE, &tmp);

  ASSERT_EQ(tmp, chec);
}

TEST(FallTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);

  for (int i = 0; i < 4; ++i) ++prms.tetramino->tetramino_state[i][Y];

  ASSERT_FALSE(check_fallen(prms.game_info->field, prms.tetramino));
  tetris_free(&prms);
}

TEST(LossTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);
  prms.game_info->field[0][3] = 2;

  ASSERT_TRUE(check_loss(prms.game_info->field));
  tetris_free(&prms);
}

TEST(IntersectionTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);

  ASSERT_FALSE(check_intersection(prms.game_info->field, prms.tetramino));
  tetris_free(&prms);
}

TEST(RightTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);
  ASSERT_FALSE(check_frame_rigth(prms.tetramino));
  tetris_free(&prms);
}

TEST(LeftTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);
  ASSERT_FALSE(check_frame_left(prms.tetramino));
  tetris_free(&prms);
}

TEST(CheckDestroyTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);
  ASSERT_FALSE(check_distroy(prms.game_info->field, 19));
  tetris_free(&prms);
}

TEST(UpdateFieldTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
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
  ASSERT_EQ(prms.game_info->field[0][3], 1);
  ASSERT_EQ(prms.game_info->field[0][4], 1);
  ASSERT_EQ(prms.game_info->field[0][5], 1);
  ASSERT_EQ(prms.game_info->field[0][6], 1);
  tetris_free(&prms);
}

TEST(UpdateFigureTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);
  tetramino_position temp = {0, 0, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 0, 0, 0};

  BLOCKS {
    temp.tetramino_state[i][X] = prms.next_tetr->tetramino_state[i][X];
    temp.tetramino_state[i][Y] = prms.next_tetr->tetramino_state[i][Y];
  }

  update_figure(prms.tetramino, prms.next_tetr);

  BLOCKS {
    ASSERT_EQ(temp.tetramino_state[i][X],
              prms.tetramino->tetramino_state[i][X]);
    ASSERT_EQ(temp.tetramino_state[i][Y],
              prms.tetramino->tetramino_state[i][Y]);
  }
  tetris_free(&prms);
}

TEST(SpawnTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);

  params_t temp = {NULL, 0, 0, NULL, NULL, 0, 0};
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
  add_figure(temp.game_info->field, temp.tetramino, (field_t)1);
  update_next_field(&temp);
  temp.tetris_state = CHECKING;

  spawn(&prms);

  BLOCKS {
    ASSERT_EQ(temp.tetramino->tetramino_state[i][X],
              prms.tetramino->tetramino_state[i][X]);
    ASSERT_EQ(temp.tetramino->tetramino_state[i][Y],
              prms.tetramino->tetramino_state[i][Y]);
  }

  FIELD
  ASSERT_EQ(temp.game_info->field[i][j], prms.game_info->field[i][j]);

  ASSERT_EQ(prms.tetris_state, temp.tetris_state);

  tetris_free(&temp);
  tetris_free(&prms);
}

TEST(PauseTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);
  pauses(&prms);

  ASSERT_EQ(prms.game_info->pause, 1);
  ASSERT_EQ(prms.tetris_state, EXIT_STATE);

  tetris_free(&prms);
}

TEST(MoveLeftTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);

  params_t temp = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&temp);
  init_tetris(&temp);
  temp.tetramino->type = prms.tetramino->type;
  temp.tetramino->state = prms.tetramino->state;
  tetraminoes(temp.tetramino->type, temp.tetramino->state,
              temp.tetramino->tetramino_state);
  add_figure(temp.game_info->field, temp.tetramino, (field_t)1);
  BLOCKS temp.X_FIGURE--;
  temp.tetramino->count_width--;
  update_field(&temp);
  temp.tetris_state = CHECKING;

  moveleft(&prms);

  BLOCKS {
    ASSERT_EQ(temp.tetramino->tetramino_state[i][X],
              prms.tetramino->tetramino_state[i][X]);
    ASSERT_EQ(temp.tetramino->tetramino_state[i][Y],
              prms.tetramino->tetramino_state[i][Y]);
  }

  ASSERT_EQ(prms.tetris_state, temp.tetris_state);
  ASSERT_EQ(prms.tetramino->count_width, temp.tetramino->count_width);

  tetris_free(&temp);
  tetris_free(&prms);
}

TEST(MoveRightTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);

  params_t temp = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&temp);
  init_tetris(&temp);
  temp.tetramino->type = prms.tetramino->type;
  temp.tetramino->state = prms.tetramino->state;
  tetraminoes(temp.tetramino->type, temp.tetramino->state,
              temp.tetramino->tetramino_state);
  add_figure(temp.game_info->field, temp.tetramino, (field_t)1);
  BLOCKS temp.X_FIGURE++;
  temp.tetramino->count_width++;
  update_field(&temp);
  temp.tetris_state = CHECKING;

  moveright(&prms);

  BLOCKS {
    ASSERT_EQ(temp.tetramino->tetramino_state[i][X],
              prms.tetramino->tetramino_state[i][X]);
    ASSERT_EQ(temp.tetramino->tetramino_state[i][Y],
              prms.tetramino->tetramino_state[i][Y]);
  }

  ASSERT_EQ(prms.tetris_state, temp.tetris_state);
  ASSERT_EQ(prms.tetramino->count_width, temp.tetramino->count_width);

  tetris_free(&temp);
  tetris_free(&prms);
}

TEST(RotateTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);

  params_t temp = {NULL, 0, 0, NULL, NULL, 0, 0};
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
    ASSERT_EQ(temp.tetramino->tetramino_state[i][X],
              prms.tetramino->tetramino_state[i][X]);
    ASSERT_EQ(temp.tetramino->tetramino_state[i][Y],
              prms.tetramino->tetramino_state[i][Y]);
  }

  ASSERT_EQ(prms.tetris_state, temp.tetris_state);

  tetris_free(&temp);
  tetris_free(&prms);
}

TEST(DestroyTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);

  init_tetris(&prms);
  for (int i = 0; i < F_WIDTH; i++) prms.game_info->field[19][i] = CONSTANT;

  distroy(&prms);

  ASSERT_EQ(prms.game_info->score, 100);
  ASSERT_EQ(prms.game_info->level, 1);
  ASSERT_EQ(prms.game_info->speed, 1);
  ASSERT_EQ(prms.tetris_state, SPAWN);

  tetris_free(&prms);
}

TEST(ConnectionTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);

  params_t temp = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&temp);
  init_tetris(&temp);
  change_tetramino(temp.tetramino, prms.tetramino);

  BLOCKS temp.game_info->field[temp.Y_FIGURE][temp.X_FIGURE] = CONSTANT;

  conection(&prms);

  ASSERT_EQ(prms.tetris_state, CHECKING);
  ASSERT_EQ(prms.flag, CONECTION);

  tetris_free(&temp);
  tetris_free(&prms);
}

TEST(ExitStateTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);
  exitstate(&prms);

  ASSERT_EQ(prms.tetris_state, EXIT_STATE);

  tetris_free(&prms);
}

TEST(GameOverTest, TestCase1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);

  gameover(&prms);

  ASSERT_EQ(prms.tetris_state, EXIT_STATE);
  ASSERT_EQ(prms.flag, GAMEOVER);

  tetris_free(&prms);
}

TEST(CheckingTest, Checking1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);

  spawn(&prms);
  check(&prms);

  EXPECT_EQ(prms.tetris_state, EXIT_STATE);
  EXPECT_EQ(prms.activity, Start);
  EXPECT_EQ(prms.flag, SPAWN);

  tetris_free(&prms);
}

TEST(CheckingTest, Checking2) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
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

  EXPECT_EQ(prms.tetris_state, EXIT_STATE);
  tetris_free(&prms);
}

TEST(CheckingTest, Checking3) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
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

  EXPECT_EQ(prms.tetris_state, GAMEOVER);
  tetris_free(&prms);
}

TEST(CheckingTest, Checking4) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
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

  EXPECT_EQ(prms.tetris_state, CONECTION);
  tetris_free(&prms);
}

TEST(CheckingTest, Checking5) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  init_tetris(&prms);

  BLOCKS prms.Y_FIGURE += 19;
  prms.flag = CONECTION;
  update_field(&prms);

  check(&prms);

  EXPECT_EQ(prms.tetris_state, DISTROY);
  tetris_free(&prms);
}

TEST(SigactTest, Test1) {
  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);
  prms.tetris_state = EXIT_STATE;

  sigact(&prms);

  EXPECT_EQ(prms.tetris_state, EXIT_STATE);

  tetris_free(&prms);
}

TEST(TetrisTest, Test1) {
  int a = userInputTetris((UserAction_t)3);
  EXPECT_EQ(a, 4);
}

TEST(TetrisTest, Test2) {
  int a = userInputTetris((UserAction_t)4);
  EXPECT_EQ(a, 4);
}

TEST(TetrisTest, Test3) {
  int a = userInputTetris((UserAction_t)5);
  EXPECT_EQ(a, 4);
}

TEST(TetrisTest, Test4) {
  int a = userInputTetris((UserAction_t)6);
  EXPECT_EQ(a, 4);
}

TEST(TetrisTest, Test5) {
  int a = userInputTetris((UserAction_t)0);
  EXPECT_EQ(a, 0);
}

TEST(TetrisTest, Test6) {
  int a = userInputTetris((UserAction_t)1);
  EXPECT_EQ(a, 1);
}

TEST(TetrisTest, Test7) {
  int a = userInputTetris((UserAction_t)2);
  EXPECT_EQ(a, 8);
}

TEST(TetrisTest, Test8) {
  int a = userInputTetris((UserAction_t)7);
  EXPECT_EQ(a, 4);
}
