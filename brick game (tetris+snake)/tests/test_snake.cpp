#include "test.hpp"

TEST(SnakeControllerTest, Test1) {
  Snake_controller s;
  GameInfo_t temp = s.updateCurrentStateSnake();

  int **field = new int *[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) field[i] = new int[F_WIDTH];
  for (int i = 0; i < F_HEIGHT; i++)
    for (int j = 0; j < F_WIDTH; j++) field[i][j] = 0;
  field[8][5] = 3;
  field[9][5] = 1;
  field[10][5] = 1;
  field[11][5] = 1;

  EXPECT_EQ(temp.field[8][5], field[8][5]);
  EXPECT_EQ(temp.field[9][5], field[9][5]);
  EXPECT_EQ(temp.field[10][5], field[10][5]);
  EXPECT_EQ(temp.field[11][5], field[11][5]);

  for (int i = 0; i < F_HEIGHT; i++) delete[] field[i];
  delete[] field;
  field = nullptr;

  //_______________________________________________________///

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 1);
}

TEST(SnakeControllerTest, Test2) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)0, false);
  GameInfo_t temp = s.updateCurrentStateSnake();

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

  //_______________________________________________________///

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 0);
}

TEST(SnakeControllerTest, Test3) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)3, false);
  GameInfo_t temp = s.updateCurrentStateSnake();

  int **field = new int *[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) field[i] = new int[F_WIDTH];
  for (int i = 0; i < F_HEIGHT; i++)
    for (int j = 0; j < F_WIDTH; j++) field[i][j] = 0;
  field[7][5] = 0;
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

  //_______________________________________________________///

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 1);
}
TEST(SnakeControllerTest, Test4) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)4, false);
  GameInfo_t temp = s.updateCurrentStateSnake();

  int **field = new int *[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) field[i] = new int[F_WIDTH];
  for (int i = 0; i < F_HEIGHT; i++)
    for (int j = 0; j < F_WIDTH; j++) field[i][j] = 0;

  field[8][5] = 1;
  field[9][5] = 1;
  field[10][5] = 1;

  EXPECT_EQ(temp.field[8][5], field[8][5]);
  EXPECT_EQ(temp.field[9][5], field[9][5]);
  EXPECT_EQ(temp.field[10][5], field[10][5]);

  for (int i = 0; i < F_HEIGHT; i++) delete[] field[i];
  delete[] field;
  field = nullptr;

  //_______________________________________________________///

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 1);
}
TEST(SnakeControllerTest, Test5) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)5, false);
  GameInfo_t temp = s.updateCurrentStateSnake();

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

  //_______________________________________________________///

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 1);
}
TEST(SnakeControllerTest, Test6) {
  Snake_controller s;

  s.userInputSnake((UserAction_t)4, false);
  s.updateCurrentStateSnake();
  GameInfo_t temp;
  s.userInputSnake((UserAction_t)6, false);
  temp = s.updateCurrentStateSnake();

  int **field = new int *[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) field[i] = new int[F_WIDTH];
  for (int i = 0; i < F_HEIGHT; i++)
    for (int j = 0; j < F_WIDTH; j++) field[i][j] = 0;
  field[7][5] = 0;
  field[8][5] = 1;
  field[9][5] = 1;
  field[10][5] = 0;

  EXPECT_EQ(temp.field[7][5], field[7][5]);
  EXPECT_EQ(temp.field[8][5], field[8][5]);
  EXPECT_EQ(temp.field[9][5], field[9][5]);
  EXPECT_EQ(temp.field[10][5], field[10][5]);

  for (int i = 0; i < F_HEIGHT; i++) delete[] field[i];
  delete[] field;
  field = nullptr;

  //_______________________________________________________///

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 1);
}

TEST(SnakeControllerTest, Test7) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)0, false);
  GameInfo_t temp = s.updateCurrentStateSnake();
  s.clear();

  int **field = new int *[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) field[i] = new int[F_WIDTH];
  for (int i = 0; i < F_HEIGHT; i++)
    for (int j = 0; j < F_WIDTH; j++) field[i][j] = 0;
  field[8][5] = 3;
  field[9][5] = 1;
  field[10][5] = 1;
  field[11][5] = 1;

  EXPECT_EQ(temp.field[8][5], field[8][5]);
  EXPECT_EQ(temp.field[9][5], field[9][5]);
  EXPECT_EQ(temp.field[10][5], field[10][5]);
  EXPECT_EQ(temp.field[11][5], field[11][5]);

  for (int i = 0; i < F_HEIGHT; i++) delete[] field[i];
  delete[] field;
  field = nullptr;

  //_______________________________________________________///

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 0);
}

TEST(SnakeControllerTest, Test9) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)3, false);
  s.updateCurrentStateSnake();
  s.userInputSnake((UserAction_t)3, false);
  s.updateCurrentStateSnake();
  s.userInputSnake((UserAction_t)3, false);
  s.updateCurrentStateSnake();
  s.userInputSnake((UserAction_t)3, false);
  s.updateCurrentStateSnake();
  s.userInputSnake((UserAction_t)3, false);
  s.updateCurrentStateSnake();
  s.userInputSnake((UserAction_t)3, false);
  s.updateCurrentStateSnake();

  EXPECT_EQ(s.get_gameover(), 1);
}

TEST(SnakeControllerTest, Test8) {
  Snake_controller s;
  int game = s.get_gameover();
  EXPECT_EQ(game, 0);
}

TEST(SnakeTest, Test1) {
  Snake_model s;
  int **temp = s.get_field();

  int **field = new int *[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) field[i] = new int[F_WIDTH];
  for (int i = 0; i < F_HEIGHT; i++)
    for (int j = 0; j < F_WIDTH; j++) field[i][j] = 0;
  field[8][5] = 3;
  field[9][5] = 1;
  field[10][5] = 1;
  field[11][5] = 1;

  EXPECT_EQ(temp[8][5], field[8][5]);
  EXPECT_EQ(temp[9][5], field[9][5]);
  EXPECT_EQ(temp[10][5], field[10][5]);
  EXPECT_EQ(temp[11][5], field[11][5]);

  for (int i = 0; i < F_HEIGHT; i++) delete[] field[i];
  delete[] field;
  field = nullptr;

  //_______________________________________________________///

  EXPECT_EQ(s.get_level(), 1);
  EXPECT_EQ(s.get_speed(), 1);
  EXPECT_EQ(s.get_score(), 0);
  EXPECT_EQ(s.get_pause(), 1);
}

TEST(SnakeTest, SetState) {
  Snake_model s;
  s.set_state((UserAction_t)0);
  EXPECT_EQ(s.get_state(), 3);
}

TEST(SnakeTest, SetActivity) {
  Snake_model s;
  s.set_activity(0);
  EXPECT_EQ(s.get_activity(), 0);
}

TEST(SnakeTest, Test5) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)3, false);
  s.userInputSnake((UserAction_t)0, false);
  GameInfo_t temp = s.updateCurrentStateSnake();

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 0);
}

TEST(SnakeTest, Test2) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)3, false);
  s.userInputSnake((UserAction_t)6, false);
  s.userInputSnake((UserAction_t)0, false);
  GameInfo_t temp = s.updateCurrentStateSnake();

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 0);
}

TEST(SnakeTest, Test3) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)4, false);
  s.userInputSnake((UserAction_t)0, false);
  GameInfo_t temp = s.updateCurrentStateSnake();

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 0);
}

TEST(SnakeTest, Test6) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)1, false);
  GameInfo_t temp = s.updateCurrentStateSnake();

  EXPECT_EQ(temp.level, 1);
  EXPECT_EQ(temp.speed, 1);
  EXPECT_EQ(temp.pause, 1);
}

TEST(SnakeControllerTest, Test10) {
  Snake_controller s;
  s.userInputSnake((UserAction_t)2, false);
  s.updateCurrentStateSnake();

  EXPECT_EQ(s.get_gameover(), 1);
}
