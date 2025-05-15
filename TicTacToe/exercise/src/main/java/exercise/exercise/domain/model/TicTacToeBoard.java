package exercise.exercise.domain.model;

public class TicTacToeBoard {
  private int[][] board;

  public TicTacToeBoard() {
    this.board = new int[3][3];
  }

  public int getElement(int row, int col) {
    if (row < 0 || row >= board.length || col < 0 || col >= board[0].length) {
      throw new IndexOutOfBoundsException();
    }
    return board[row][col];
  }

  public void setElement(int row, int col, int value) {
    if (row < 0 || row >= board.length || col < 0 || col >= board[0].length) {
      throw new IndexOutOfBoundsException();
    }
    board[row][col] = value;
  }
}
