package Rogue.Datalayer;

public class GameStatistics {
  private String playerName, lastStattistics;
  private boolean win;
  private int score, expirence;

  public GameStatistics() {
    this.lastStattistics = "";
    this.playerName = "player";
    this.win = false;
    this.score = 0;
  }

  public void updateWin(boolean win) {
    this.win = win;
  }

  public void updateScore(int score) {
    this.score = score;
  }

  public void updateExpirence(int expirence) {
    this.expirence = expirence;
  }

  public void updatePlayerName(String playerName) {
    this.playerName = playerName;
  }

  public void updateLastStattistics(String lastStattistics) {
    this.lastStattistics = lastStattistics;
  }

  public boolean getWin() {
    return win;
  }

  public int getScore() {
    return score;
  }

  public int getExpirence() {
    return expirence;
  }

  public String getPlayerName() {
    return playerName;
  }

  public String getLastStattistics() {
    return lastStattistics;
  }
}