#include "snake_fsm.hpp"
using namespace s21;

Snake_fsm *Snake_fsm::get_snake() {
  static Snake_fsm snake;
  return &snake;
}

void Snake_fsm::snake_game() {
  if (!gameover) {
    if (state == SNAKE_PAUSE)
      pause();
    else if (state == SNAKE_SPAWN)
      spawn();
    else if (state == SNAKE_SHIFTING)
      shifting();
    else if (state == SNAKE_MOVING)
      move();
    else if (state == SNAKE_CONECTION)
      conection();
    else if (state == SNAKE_CHECKING)
      checking();
    else if (state == SNAKE_GROW)
      growing();
    else if (state == SNAKE_GAME_OVER)
      game_over();
    else if (state == SNAKE_EXIT_STATE)
      exit_state();
  } else
    state = SNAKE_EXIT_STATE;
}

void Snake_fsm::set_state(UserAction_t action) {
  if (action == Start) {
    info.pause = 0;
    state = SNAKE_SHIFTING;
  } else if (action == Pause)
    state = SNAKE_PAUSE;
  else if (action == Left)
    state = SNAKE_MOVING;
  else if (action == Right)
    state = SNAKE_MOVING;
  else if (action == Up)
    state = SNAKE_MOVING;
  else if (action == Down)
    state = SNAKE_MOVING;
  else if (action == Action)
    check_timer();
  else if (action == Terminate)
    state = SNAKE_GAME_OVER;
}

void Snake_fsm::set_snake_head() {
  if (derect == UP)
    snake.insert(snake.begin(),
                 std::make_pair(snake[0].first - 1, snake[0].second));
  else if (derect == DOWN)
    snake.insert(snake.begin(),
                 std::make_pair(snake[0].first + 1, snake[0].second));
  else if (derect == LEFT)
    snake.insert(snake.begin(),
                 std::make_pair(snake[0].first, snake[0].second - 1));
  else if (derect == RIGHT)
    snake.insert(snake.begin(),
                 std::make_pair(snake[0].first, snake[0].second + 1));
}

void Snake_fsm::shifting() {
  set_snake_head();
  snake.pop_back();
  state = SNAKE_CHECKING;
  timer = std::chrono::steady_clock::now();
}

void Snake_fsm::move() {
  if (derect != RIGHT && activity == Left)
    derect = LEFT;
  else if (derect != LEFT && activity == Right)
    derect = RIGHT;
  else if (derect != DOWN && activity == Up)
    derect = UP;
  else if (derect != UP && activity == Down)
    derect = DOWN;
  state = SNAKE_SHIFTING;
}

void Snake_fsm::check_timer() {
  if (std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::steady_clock::now() - timer)
          .count() >= FALL_DELAY) {
    state = SNAKE_SHIFTING;
  } else
    state = SNAKE_CHECKING;
}

void Snake_fsm::spawn() {
  init_apple();
  set_field();
  state = SNAKE_EXIT_STATE;
}

void Snake_fsm::growing() {
  snake_length++;
  snake.push_back(
      std::make_pair(snake[snake_length].first, snake[snake_length].second));
  eat_apples.erase(eat_apples.begin());
}

void Snake_fsm::conection() {
  info.score++;
  if (NEW_LEVEL) {
    info.level++;
    info.speed++;
  }

  if (info.score > info.highscore) info.highscore = info.score;
  state = (info.score == FINAL_SCORE ? SNAKE_GAME_OVER : SNAKE_SPAWN);
}

void Snake_fsm::game_over() {
  gameover = true;
  info.pause = 2;
  state = SNAKE_EXIT_STATE;
}

void Snake_fsm::pause() {
  info.pause = 1;
  state = SNAKE_EXIT_STATE;
}

void Snake_fsm::checking() {
  if (check_die()) {
    state = SNAKE_GAME_OVER;
  } else if (snake[0].second == apple.first && snake[0].first == apple.second) {
    state = SNAKE_CONECTION;
    eat_apples.push_back(apple);
  } else {
    set_field();
    state = SNAKE_EXIT_STATE;
  }

  if (eat_apples.size() > 0 && eat_apples[0].first == snake.back().second &&
      eat_apples[0].second == snake.back().first)
    growing();
}

bool Snake_fsm::check_die() {
  bool result = false;

  if (snake[0].first == -1 || snake[0].second == -1 ||
      snake[0].first == F_HEIGHT || snake[0].second == F_WIDTH ||
      snake[snake_length].first == -1 || snake[snake_length].second == -1 ||
      snake[snake_length].first == F_HEIGHT ||
      snake[snake_length].second == F_WIDTH)
    result = true;

  if (!result)
    for (int i = 1; i < snake_length; i++)
      if (snake[0] == snake[i]) result = true;

  return result;
}
