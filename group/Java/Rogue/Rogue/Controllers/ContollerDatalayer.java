package Controllers;

import Datalayer.GameData;
import Datalayer.GameDataAndStatistics;
import Datalayer.GameDataHandler;
import Datalayer.GameStatistics;

import Domain.Game.Control.PrintMap;

public class ContollerDatalayer {

  private GameDataHandler dataHandler;
  private GameDataAndStatistics dataAndStatistics;

  public ContollerDatalayer() {
    dataHandler = new GameDataHandler();
    dataAndStatistics = dataHandler.loadGameDataAndStatistics();
    if (dataAndStatistics == null)
      dataAndStatistics = new GameDataAndStatistics();
  }

  public void saveGame(PrintMap printMap) {
    if (printMap.isNewFloor() || !printMap.heroAlive()) {
      save(printMap);
      printMap.setNewFloor(false);
    }

    if (!printMap.heroAlive()) {
      returnStatistics(printMap);
      save(printMap);
    }
  }

  private void save(PrintMap map) {
    if (dataAndStatistics == null) {
      dataAndStatistics = new GameDataAndStatistics();
    }
    if (dataAndStatistics.getGameData() == null)
      dataAndStatistics.setGameData(new GameData());
    if (dataAndStatistics.getStatistics() == null)
      dataAndStatistics.setStatistics(new GameStatistics());

    dataAndStatistics.getGameData().setGameData(map.getFloor(), map.getPlayer());
    dataHandler.saveGameDataAndStatistics(dataAndStatistics);
  }

  public void loadGame(PrintMap map) {
    if (dataAndStatistics != null) {
      GameData data = dataAndStatistics.getGameData();
      if (data != null && data.getHero().getHealth() > 0) {
        map.setFloor(data.getFloor());
        int x = map.getPlayer().getPosition().x();
        int y = map.getPlayer().getPosition().y();
        map.setPlayer(data.getHero());
        map.getPlayer().setPosition(x, y);
      }
    }
  }

  private void returnStatistics(PrintMap map) {
    dataHandler.updateStatistics(dataAndStatistics, map.heroAlive());
    String temp = dataAndStatistics.getStatistics().getLastStattistics();
    map.setGameStatistic(String.format(
        "%s%n%10s - %s,\texp:\t%d,\tgold:\t%d", temp != null ? temp : "",
        dataAndStatistics.getStatistics().getPlayerName(),
        dataAndStatistics.getStatistics().getWin() ? "win" : "lose", dataAndStatistics.getStatistics().getExpirence(),
        dataAndStatistics.getStatistics().getScore()));
    dataAndStatistics.getStatistics().updateLastStattistics(map.getGameStatistic());
  }
}
 