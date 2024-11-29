package Rogue.View;

import Rogue.Domain.Game.Control.PrePrint;
import Rogue.View.TheMostImportantDirectory.Pictures;
import Rogue.View.TheMostImportantDirectory.Result;

public class Logo {
  private char[][] printChar;

  public Logo(char[][] printChar) {
    this.printChar = printChar;
  }

  public void printFirstScreen() {
    printLogo();
    sleep(3000);
    printGameName();
  }

  public void printEndLogo(char[][] printChar, boolean heroAlive, boolean isWin, String gameStatistic) {
    if (heroAlive) {
      printResult(printChar, isWin);
    }

    printChar = Pictures.getLogo2();
    if (!heroAlive && gameStatistic != null)
      printChar[28] = gameStatistic.toCharArray();
    Rogue.View.IO.print(printChar);
  }

  private void printLogo() {
    printChar = Pictures.getLogo1();
    Rogue.View.IO.print(printChar);
  }

  private void printGameName() {
    printChar = Pictures.getGameName();
    Rogue.View.IO.print(printChar);
  }

  private void printResult(char[][] printChar, boolean isWin) {
    printChar = isWin ? Result.getWin() : Result.getLose();
    Rogue.View.IO.print(printChar);
    sleep(3000);
  }

  private void sleep(int ms) {
    try {
      Thread.sleep(ms);
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
      e.printStackTrace();
    }
  }
}