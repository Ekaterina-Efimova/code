package exercise.exercise.domain.service;

import exercise.exercise.domain.model.Game;

public interface TicTacToeService {
  void getNextMove(Game game);

  boolean validateBoard(int[][] lastBoard, int[][] currentBoard);

  boolean isGameOver(int[][] board);
}
