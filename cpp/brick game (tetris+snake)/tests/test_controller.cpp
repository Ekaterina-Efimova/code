#include "test.hpp"
TEST(ControllerTest, Test0) {
  int *game = get_game();
  EXPECT_EQ(*game, -1);
}

TEST(ControllerTest, Test1) {
  int *game = get_game();
  *game = 1;
  GameInfo_t temp = updateCurrentState();

  int **field = new int *[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) field[i] = new int[F_WIDTH];
  for (int i = 0; i < F_HEIGHT; i++)
    for (int j = 0; j < F_WIDTH; j++) field[i][j] = 0;
  field[8][5] = 3;
  field[9][5] = 1;
  field[10][5] = 1;
  field[11][5] = 1;
  for (int i = 0; i < F_HEIGHT; ++i)
    for (int j = 0; j < F_WIDTH; ++j) EXPECT_EQ(temp.field[i][j], field[i][j]);
  for (int i = 0; i < F_HEIGHT; i++) delete[] field[i];
  delete[] field;
  field = nullptr;

  //_______________________________________________________///

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.score, 0);
  EXPECT_EQ(temp.pause, 1);
}

TEST(ControllerTest, Test2) {
  int *game = get_game();
  *game = 2;
  bool *g_o = gameOver();
  GameInfo_t temp = updateCurrentState();

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.score, 0);
  EXPECT_EQ(temp.pause, 1);
  EXPECT_FALSE(*g_o);
}

TEST(ControllerTest, Test3) {
  int *game = get_game();
  *game = 1;
  userInput((UserAction_t)0, false);
  GameInfo_t temp = updateCurrentState();
  int **field = new int *[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) field[i] = new int[F_WIDTH];
  for (int i = 0; i < F_HEIGHT; i++)
    for (int j = 0; j < F_WIDTH; j++) field[i][j] = 0;
  field[7][5] = 3;
  field[8][5] = 1;
  field[9][5] = 1;
  field[10][5] = 1;
  EXPECT_EQ(temp.field[7][5], field[7][5]);
  EXPECT_EQ(temp.field[8][5], field[8][5]);
  EXPECT_EQ(temp.field[9][5], field[9][5]);
  EXPECT_EQ(temp.field[10][5], field[10][5]);

  for (int i = 0; i < F_HEIGHT; i++) delete[] field[i];
  delete[] field;
  field = nullptr;
}

TEST(ControllerTest, Test4) {
  int *game = get_game();
  *game = 1;

  userInput((UserAction_t)2, false);
  updateCurrentState();
  bool *g_o = gameOver();
  EXPECT_TRUE(*g_o);
}

TEST(ControllerTest, Test5) {
  int *game = get_game();
  *game = 2;

  userInput((UserAction_t)2, false);
  updateCurrentState();
  bool *g_o = gameOver();
  EXPECT_TRUE(*g_o);
}

TEST(ControllerTest, Test8) {
  int *game = get_game();
  *game = 2;
  userInput((UserAction_t)0, false);
  GameInfo_t temp = updateCurrentState();

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.score, 0);
  EXPECT_EQ(temp.pause, 1);
}

TEST(ControllerTest, Test7) {
  int *game = get_game();
  *game = 2;
  bool *g_o = gameOver();
  *g_o = true;
  GameInfo_t temp = updateCurrentState();

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.score, 0);
  EXPECT_EQ(temp.pause, 1);
  EXPECT_TRUE(*g_o);
}

TEST(ControllerTest, Test6) {
  int *game = get_game();
  *game = 1;
  bool *g_o = gameOver();
  *g_o = true;
  GameInfo_t temp = updateCurrentState();

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.score, 0);
  EXPECT_EQ(temp.pause, 1);
  EXPECT_TRUE(*g_o);
}

TEST(ControllerTest, GetGame) {
  int *game = get_game();
  *game = 1;
  EXPECT_EQ(*game, 1);
}

TEST(ControllerTest, GetGame2) {
  int *game = get_game();
  *game = 3;
  userInput((UserAction_t)0, false);

  EXPECT_EQ(*game, 3);
}

TEST(ControllerTest, GetGame3) {
  int *game = get_game();
  *game = 3;
  updateCurrentState();

  EXPECT_EQ(*game, 3);
}

TEST(ControllerTest, GetSnakeGame) {
  Snake_controller *s = nullptr;
  s = get_snake_game();
  ASSERT_TRUE(s != nullptr);
}

TEST(ControllerTest, GetTetrisGame) {
  params_t *t = nullptr;
  t = get_tetris_game();
  ASSERT_TRUE(t != nullptr);
}

TEST(ControllerTest, GameOver) {
  bool *b = nullptr;
  b = gameOver();
  ASSERT_TRUE(b != nullptr);
}