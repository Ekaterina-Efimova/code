package exercise.exercise.datasource.model;

import java.util.UUID;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class GameEntity {
  private UUID gameId;
  private int[][] board;
  private String message;

  public GameEntity() {
    this.gameId = null;
    this.board = new int[3][3];
    this.message = null;
  }

  public int getElement(int row, int col) {
    if (row < 0 || row >= board.length || col < 0 || col >= board[0].length) {
      throw new IndexOutOfBoundsException();
    }
    return board[row][col];
  }

  public void setElement(int row, int col, int value) {
    if  (row < 0 || row >= board.length || col < 0 || col >= board[0].length) {
      throw new IndexOutOfBoundsException();
    }
    board[row][col] = value;
  }
}
