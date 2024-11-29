package Rogue.Controllers;

import Rogue.Domain.Game.Objects.Map;
import Rogue.View.Logo;

public class ControllerView {
  private char[][] printChar;
  private Logo logo;

  public ControllerView() {
    printChar = new char[Map.MAP_HEIGHT + 3][100];
    logo = new Logo(printChar);
  }

  public void printFirstScreen() {
    logo.printFirstScreen();
  }

  public void printEndLogo(boolean heroAlive, boolean isWin, String gameStatistic) {
    logo.printEndLogo(printChar, heroAlive, isWin, gameStatistic);
  }

  public String printHeroName() {
    String heroName = askName();
    clearPrintChar();
    printChar[0] = String.format(" Привет, %s", heroName).toCharArray();
    return heroName;
  }

  public String askName() {
    printChar[Map.MAP_HEIGHT + 2] = "Введите имя героя: ".toCharArray();
    Rogue.View.IO.print(printChar);
    return Rogue.View.IO.getString();
  }

  public void draw() {
    Rogue.View.IO.print(printChar);
    clearPrintChar();
  }

  public char getGame() {
    char c;
    do {
      c = userInput();
    } while (c != 'n' && c != 'N' && c != ' ');
    return c;
  }

  public char userInput(){
    return Rogue.View.IO.getCh();
  }

  private void clearPrintChar() {
    printChar[Map.MAP_HEIGHT + 2] = "".toCharArray();
  }

  public char[][] getPrintChar() {
    return printChar;
  }
}
