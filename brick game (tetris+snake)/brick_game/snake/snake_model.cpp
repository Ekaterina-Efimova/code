#include "snake_model.hpp"

using namespace s21;

Snake_model::Snake_model()
    : activity(Pause),
      state(SNAKE_PAUSE),
      snake_length(SNAKE_LENGTH - 1),
      derect(UP),
      gameover(false),
      hold(false),
      conect(0) {
  gen = std::mt19937(rd());
  dis_width = std::uniform_int_distribution<>(0, F_WIDTH - 1);
  dis_height = std::uniform_int_distribution<>(0, F_HEIGHT - 1);

  init_game_info();
  snake = {{8, 5}, {9, 5}, {10, 5}, {11, 5}};
  init_apple();
  set_field();

  info.score = 0;
  read_score();
  info.level = 1;
  info.speed = 1;
  info.pause = 1;
};

Snake_model::~Snake_model() {
  if (info.score == info.highscore) write_score();

  if (info.field) {
    for (int i = 0; i < F_HEIGHT; i++) delete[] info.field[i];
    delete[] info.field;
    info.field = nullptr;
  }

  if (info.next) {
    for (int i = 0; i < NEXT_HEIGHT; i++) delete[] info.next[i];
    delete[] info.next;
    info.next = nullptr;
  }
}

void Snake_model::init_apple() {
  do {
    apple.first = dis_width(gen);
    apple.second = dis_height(gen);
  } while (check_apple_coord());
}

bool Snake_model::check_apple_coord() {
  bool result = std::any_of(snake.begin(), snake.end(), [this](const auto &s) {
    return s.second == apple.first && s.first == apple.second;
  });

  return result;
}

void Snake_model::init_game_info() {
  malloc_field();
  init_next_field();
  read_score();
}

void Snake_model::malloc_field() {
  info.field = new int *[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) info.field[i] = new int[F_WIDTH];
}

void Snake_model::empty_field() {
  for (int i = 0; i < F_HEIGHT; i++)
    for (int j = 0; j < F_WIDTH; j++) info.field[i][j] = SNAKE_EMPTY;
}

void Snake_model::set_field() {
  empty_field();
  put_snake();
  info.field[apple.second][apple.first] = APPLE;
}

void Snake_model::put_snake() {
  for (auto s : snake) info.field[s.first][s.second] = SNAKE;
  info.field[snake[0].first][snake[0].second] = SNAKE_HEAD;
}

void Snake_model::init_next_field() {
  info.next = new int *[NEXT_HEIGHT];
  for (int i = 0; i < NEXT_HEIGHT; i++) info.next[i] = new int[NEXT_WIDTH];
  for (int i = 0; i < NEXT_HEIGHT; i++)
    for (int j = 0; j < NEXT_HEIGHT; j++) info.next[i][j] = SNAKE_EMPTY;
}

void Snake_model::write_score() {
  std::ofstream file(SNAKE_FILE);
  if (file.is_open()) {
    file << info.highscore;
    file.close();
  }
}

void Snake_model::read_score() {
  std::ifstream file(SNAKE_FILE);
  if (file.is_open()) {
    file >> info.highscore;
    file.close();
  }
};
