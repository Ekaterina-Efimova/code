package Rogue.Controllers;

import Rogue.Datalayer.GameData;
import Rogue.Datalayer.GameDataAndStatistics;
import Rogue.Datalayer.GameDataHandler;
import Rogue.Datalayer.GameStatistics;
import Rogue.Domain.Character.Control.Hero;
import Rogue.Domain.Game.Control.PrePrint;

public class ContollerDatalayer {

  private GameDataHandler dataHandler;
  private GameDataAndStatistics dataAndStatistics;
  private String gameStatistic;

  public ContollerDatalayer() {
    dataHandler = new GameDataHandler();
    dataAndStatistics = dataHandler.loadGameDataAndStatistics();
    if (dataAndStatistics == null)
      dataAndStatistics = new GameDataAndStatistics();
    gameStatistic = null;
  }

  public void saveGame(PrePrint prePrint) {
    if (prePrint.isNewFloor() || !prePrint.heroAlive()) {
      save(prePrint);
    }

    if (!prePrint.heroAlive()) {
      returnStatistics(prePrint);
      save(prePrint);
    }
  }

  private void save(PrePrint prePrint) {
    if (dataAndStatistics == null) {
      dataAndStatistics = new GameDataAndStatistics();
    }
    if (dataAndStatistics.getGameData() == null)
      dataAndStatistics.setGameData(new GameData());
    if (dataAndStatistics.getStatistics() == null)
      dataAndStatistics.setStatistics(new GameStatistics());

    dataAndStatistics.getGameData().setGameData(prePrint.getFloor(), prePrint.getPlayer());
    dataHandler.saveGameDataAndStatistics(dataAndStatistics);
  }

  public PrePrint loadGame() {
    PrePrint prePrint = null;

    if ( dataAndStatistics != null) {
      GameData data = dataAndStatistics.getGameData();

      if (data != null && data.getHero().getHealth() > 0) {
        Hero hero = data.getHero();
        prePrint = new PrePrint(hero);
        prePrint.setFloor(data.getFloor());
      } 
    } 

    return prePrint;
  }

  private void returnStatistics(PrePrint prePrint) {
    dataHandler.updateStatistics(dataAndStatistics, prePrint.heroAlive());
    String temp = dataAndStatistics.getStatistics().getLastStattistics();

   gameStatistic = String.format(
        "%s%n%10s - %s,\texp:\t%d,\tgold:\t%d", temp != null ? temp : "",
        dataAndStatistics.getStatistics().getPlayerName(),
        dataAndStatistics.getStatistics().getWin() ? "win" : "lose", dataAndStatistics.getStatistics().getExpirence(),
        dataAndStatistics.getStatistics().getScore());

    dataAndStatistics.getStatistics().updateLastStattistics(gameStatistic);
  }

  public String getGameStatistic() {
    return gameStatistic;
  }
}
