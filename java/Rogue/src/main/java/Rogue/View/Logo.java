package Rogue.View;

import Rogue.Controllers.ControllerDatalayer;
import Rogue.Domain.Game.Control.GameData;
import Rogue.View.TheMostImportantDirectory.Pictures;
import Rogue.View.TheMostImportantDirectory.Result;
import java.util.logging.Level;
import java.util.logging.Logger;

public final class Logo {
  private Logo() {
  }

  public static void printFirstScreen() {
    printLogo();
    sleep(3000);
    printGameName();
  }

  public static void printEndLogo() {
    boolean heroDead = GameData.getInstance().getHero().getHealth() <= 0;
    boolean isWin = GameData.getInstance().getHero().getFloor() == 21;

    String gameStatistic = null;
    if (heroDead) {
      gameStatistic = ControllerDatalayer.getGameStatistic();
      printResult(isWin);
    }

    char[][] printChar = Pictures.getLogo2();
    if (heroDead && gameStatistic != null)
      printChar[28] = gameStatistic.toCharArray();
    Rogue.View.IO.print(printChar);
  }

  private static void printLogo() {
    Rogue.View.IO.print(Pictures.getLogo1());
  }

  private static void printGameName() {
    Rogue.View.IO.print(Pictures.getGameName());
  }

  private static void printResult(boolean isWin) {
    char[][] printChar = isWin ? Result.getWin() : Result.getLose();
    Rogue.View.IO.print(printChar);
    sleep(3000);
  }

  private static void sleep(int ms) {
    try {
      Thread.sleep(ms);
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
      Logger.getLogger(Logo.class.getName()).log(Level.SEVERE, "An error occurred", e);
    }
  }
}