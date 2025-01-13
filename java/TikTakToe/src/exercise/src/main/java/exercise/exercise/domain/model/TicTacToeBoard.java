package exercise.exercise.domain.model;

public class TicTacToeBoard {
  private int[][] board;

  public TicTacToeBoard() {
    this.board = new int[3][3];
  }

  public void setTicTacToeBoard(int[][] board) {
    this.board = new int[3][3];
    for (int i = 0; i < 3; i++) {
      System.arraycopy(board[i], 0, this.board[i], 0, 3);
    }
  }

  public int[][] getBoard() {
    return board;
  }

  public void setBoard(int[][] board) {
    this.board = board;
  }
}
