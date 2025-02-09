package exercise.exercise.domain.service;

import exercise.exercise.domain.model.Game;

public interface TicTacToeService {
  Game getNextMove(Game game, String move);
}
