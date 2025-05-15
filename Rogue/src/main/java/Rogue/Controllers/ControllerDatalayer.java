package Rogue.Controllers;

import Rogue.Datalayer.GameDataAndStatistics;
import Rogue.Datalayer.GameDataHandler;
import Rogue.Datalayer.GameStatistics;
import Rogue.Domain.Game.Control.GameData;
import Rogue.Domain.Game.Objects.Character.Hero;

public final class ControllerDatalayer {
  private static GameDataAndStatistics dataAndStatistics;

  private ControllerDatalayer() {
  }

  public static Hero loadGame() {
    Hero hero = null;

    GameDataHandler dataHandler = GameDataHandler.getGameDataHandler();
    dataAndStatistics = dataHandler.loadGameDataAndStatistics();
    if (dataAndStatistics != null) {
      Hero hero2 = dataAndStatistics.getHero();

      if (hero2 != null && hero2.getHealth() > 0) {
        hero = hero2;
      }
    }

    return hero;
  }

  public static void saveGame() {
    GameDataHandler dataHandler = GameDataHandler.getGameDataHandler();
    if (dataAndStatistics == null)
      dataAndStatistics = new GameDataAndStatistics();

    if (dataAndStatistics.getStatistics() == null)
      dataAndStatistics.setStatistics(new GameStatistics());

    Hero hero = GameData.getInstance().getHero();
    dataAndStatistics.setHero(hero);
    dataHandler.saveGameDataAndStatistics(dataAndStatistics);
  }

  public static String getGameStatistic() {
    if (dataAndStatistics == null)
      dataAndStatistics = new GameDataAndStatistics();

    String temp = dataAndStatistics.getStatistics().getLastStatistics();
    Hero hero = GameData.getInstance().getHero();
    String gameStatistic = String.format(
        "%s%n%s - сокровища: %d, уровень: %d, убито монстров %d, съедено еды %d, выпито эликсиров %d, прочитано свитков %d, нанесено ударов %d, пропущено ударов %d, сделано шагов %d.",
        temp, hero.getName(), hero.getGold(), hero.getLevel(), hero.getKills(), hero.getFoodEat(),
        hero.getElixirDrink(), hero.getScrollRead(), hero.getHitOk(), hero.getHitMiss(), hero.getSteps());

    dataAndStatistics.getStatistics().updateLastStatistics(gameStatistic);
    saveGame();

    return dataAndStatistics.getStatistics().getLastStatistics();
  }
}
