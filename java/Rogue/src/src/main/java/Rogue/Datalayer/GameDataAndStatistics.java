package Rogue.Datalayer;

public class GameDataAndStatistics {
  private GameData gameData;
  private GameStatistics statistics;

  public GameData getGameData() {
    return gameData;
  }

  public GameStatistics getStatistics() {
    return statistics;
  }

  public void setGameData(GameData gameData) {
    this.gameData = gameData;
  }

  public void setStatistics(GameStatistics statistics) {
    this.statistics = statistics;
  }
}