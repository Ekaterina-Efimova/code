package exercise.exercise.domain.service;

import exercise.exercise.domain.model.Game;
import exercise.exercise.web.model.GameWeb;

public interface TicTacToeService {
  Game getNextMove(Game game, GameWeb gameWeb);
}
