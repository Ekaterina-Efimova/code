package exercise.exercise.domain.service;

import org.springframework.stereotype.Service;

import exercise.exercise.domain.model.Game;

@Service
public class TicTacToeServiceImpl implements TicTacToeService {
  private int[][] tempBoard;

  public TicTacToeServiceImpl() {
    tempBoard = new int[3][3];
  }

  public void getNextMove(Game game) {
    tempBoard = copyBoard(game.getBoard().getBoard());
    int[] computerMove = minimax();

    if (!validateComputerMove(computerMove))
      game.setError("Некорректный ход компьютера");
    else if (!validateBoard(game.getBoard().getBoard()))
      game.setError("Некорректное поле");
    else
      game.getBoard().getBoard()[computerMove[0]][computerMove[1]] = 2;
  }

  public boolean validateBoard(int[][] lastBoard, int[][] currentBoard) {
    boolean result = true;
    int count = 0;
    for (int i = 0; i < 3 && count < 2; i++) {
      for (int j = 0; j < 3 && count < 2; j++) {
        if (lastBoard[i][j] != currentBoard[i][j]) {
          count++;
        }
        if (count == 2) {
          result = false;
        }
      }
    }
    return result;
  }

  public boolean isGameOver(int[][] board) {
    boolean result = true;

    for (int i = 0; i < 3 && result; i++) {
      for (int j = 0; j < 3 && result; j++) {
        if (board[i][j] == 0) {
          result = false;
        }
      }
    }

    for (int i = 0; i < 3 && !result; i++)
      if ((board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2])
          || (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i]))
        result = true;

    if (!result && (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        || (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0]))
      result = true;

    return result;
  }

  private int[] minimax() {
    Minimax minimax = new Minimax();
    return minimax.findOptimalMovement(tempBoard);
  }

  private int[][] copyBoard(int[][] originalBoard) {
    int[][] copiedBoard = new int[3][3];
    for (int i = 0; i < 3; i++) {
      System.arraycopy(originalBoard[i], 0, copiedBoard[i], 0, 3);
    }
    return copiedBoard;
  }

  private boolean validateBoard(int[][] board) {
    boolean result = true;
    for (int i = 0; i < 3 && !result; i++) {
      for (int j = 0; j < 3 && !result; j++) {
        if (tempBoard[i][j] != board[i][j]) {
          result = false;
        }
      }
    }
    return result;
  }

  private boolean validateComputerMove(int[] computerMove) {
    return !(computerMove == null || computerMove[0] < 0 || computerMove[0] > 2 || computerMove[1] < 0
        || computerMove[1] > 2);
  }

}