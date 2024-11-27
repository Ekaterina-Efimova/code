package View;

import View.TheMostImportantDirectory.Pictures;
import View.TheMostImportantDirectory.Result;
import Domain.Game.Control.PrintMap;

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

  public void printEndLogo(PrintMap printMap) {
    if (!printMap.heroAlive()) {
      printResult(printMap);
    }
    
    printChar = Pictures.logo2;
    if (!printMap.heroAlive())
      printMap.printGameStatistic(printChar);
    View.IO.print(printChar);
  }

  private void printLogo() {
    printChar = Pictures.logo1;
    View.IO.print(printChar);
  }

  private void printGameName() {
    printChar = Pictures.gameName;
    View.IO.print(printChar);
  }

  private void printResult(PrintMap printMap) {
    printChar = printMap.getFloor() == 21 ? Result.win : Result.lose;
    View.IO.print(printChar);
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
