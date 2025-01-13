package exercise.exercise.datasource.model;

import java.util.UUID;

public class GameEntity {
  private UUID gameId;
  private TicTacToeBoardEntity board;
  private String move;
  private boolean gameOver;
  private String error;

  public GameEntity() {
    this.gameId = UUID.randomUUID();
    this.board = new TicTacToeBoardEntity();
    this.gameOver = false;
    this.error = null;
  }

  public void setMove(String move) {
    this.move = move;
    if (move != null) {
      String[] coordinates = move.split(",");
      int row = Integer.parseInt(coordinates[0]);
      int col = Integer.parseInt(coordinates[1]);
      this.board.getBoard()[row][col] = 1;
    }
  }

  public String getPlayerMove() {
    return move;
  }

  public String getError() {
    return error;
  }

  public void setError(String error) {
    this.error = error;
  }

  public UUID getGameId() {
    return gameId;
  }

  public TicTacToeBoardEntity getBoard() {
    return board;
  }

  public void setGameId(UUID gameId) {
    this.gameId = gameId;
  }

  public void setGameOver(boolean gameOver) {
    this.gameOver = gameOver;
  }

  public boolean isGameOver() {
    return gameOver;
  }

  public void setBoard(TicTacToeBoardEntity board) {
    this.board = board;
  }
}
