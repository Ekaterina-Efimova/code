package exercise.exercise.domain.service;

import java.util.stream.IntStream;

import exercise.exercise.domain.model.Game;
import exercise.exercise.web.model.GameWeb;

public class TicTacToeServiceImpl implements TicTacToeService {
  private int[][] tempBoard;

  public TicTacToeServiceImpl() {
    tempBoard = new int[3][3];
  }

  public Game getNextMove(Game game, GameWeb gameWeb) {
    if (game.getMessage() == null) {

      if (!validateBoard(gameWeb)) {
        game.setMessage("Некорректное поле игрока");
        return game;
      }

      game.setMove(gameWeb.getMove());
      tempBoard = copyBoard(game);
      int[] computerMove = minimax();

      if (!validateComputerMove(computerMove))
        game.setMessage("Некорректный ход компьютера");
      else if (!validateBoard(game))
        game.setMessage("Некорректное поле компьютера");

      else
        game.getBoard().setElement(computerMove[0], computerMove[1], 2);

      if (isGameOver(game))
        game.setMessage("Игра окончена");

    }

    return game;
  }

  private int[] minimax() {
    Minimax minimax = new Minimax();
    return minimax.findOptimalMovement(tempBoard);
  }

  private boolean isGameOver(Game game) {
    boolean result = true;

    for (int i = 0; i < 3 && result; i++) {
      for (int j = 0; j < 3 && result; j++) {
        if (game.getBoard().getElement(i, j) == 0) {
          result = false;
        }
      }
    }

    for (int i = 0; i < 3 && !result; i++)
      if ((game.getBoard().getElement(i, 0) != 0
          && game.getBoard().getElement(i, 0) == game.getBoard().getElement(i, 1)
          && game.getBoard().getElement(i, 1) == game.getBoard().getElement(i, 2))
          || (game.getBoard().getElement(0, i) != 0
              && game.getBoard().getElement(0, i) == game.getBoard().getElement(1, i)
              && game.getBoard().getElement(1, i) == game.getBoard().getElement(2, i)))
        result = true;

    if (!result
        && (game.getBoard().getElement(0, 0) != 0
            && game.getBoard().getElement(0, 0) == game.getBoard().getElement(1, 1)
            && game.getBoard().getElement(1, 1) == game.getBoard().getElement(2, 2))
        || (game.getBoard().getElement(0, 2) != 0
            && game.getBoard().getElement(0, 2) == game.getBoard().getElement(1, 1)
            && game.getBoard().getElement(1, 1) == game.getBoard().getElement(2, 0)))
      result = true;

    return result;
  }

  private int[][] copyBoard(Game game) {
    int[][] copiedBoard = new int[3][3];

    IntStream.range(0, 3)
        .forEachOrdered(i -> IntStream.range(0, 3)
            .forEachOrdered(j -> copiedBoard[i][j] = game.getBoard().getElement(i, j)));

    return copiedBoard;
  }

  private boolean validateBoard(GameWeb gameWeb) {
    return IntStream.range(0, 3)
        .allMatch(i -> IntStream.range(0, 3)
            .allMatch(j -> gameWeb.getElement(i, j) == 0));

  }

  private boolean validateBoard(Game game) {
    return IntStream.range(0, 3)
        .allMatch(i -> IntStream.range(0, 3)
            .allMatch(j -> tempBoard[i][j] == game.getBoard().getElement(i, j)));

  }

  private boolean validateComputerMove(int[] computerMove) {
    return !(computerMove == null || computerMove[0] < 0 || computerMove[0] > 2 || computerMove[1] < 0
        || computerMove[1] > 2);
  }

}