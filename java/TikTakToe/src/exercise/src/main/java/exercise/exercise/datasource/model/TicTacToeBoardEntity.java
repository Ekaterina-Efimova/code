package exercise.exercise.datasource.model;

public class TicTacToeBoardEntity {
  private int[][] board;

  public TicTacToeBoardEntity() {
    this.board = new int[3][3];
  }
  
  public void setBoard(int[][] board) {
    this.board = new int[3][3];
    for (int i = 0; i < 3; i++) {
      System.arraycopy(board[i], 0, this.board[i], 0, 3);
    }
  }

  public int[][] getBoard() {
    return board;
  }
}
