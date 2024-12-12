package Rogue.Controllers;

import Rogue.Domain.Game.Objects.Map;
import Rogue.View.Logo;

public final class ControllerView {
  private final char[][] printChar;

  public ControllerView() {
    printChar = new char[Map.MAP_HEIGHT + 3][100];
  }

  public void printFirstScreen() {
    Logo.printFirstScreen();
  }

  public void printEndLogo() {
    Logo.printEndLogo();
  }

  public String printHeroName() {
    String heroName = askName();
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
  }

  public char getNewGameChoice() {
    char c;
    do {
      c = userInput();
    } while (c != 'n' && c != 'N' && c != ' ');
    return c;
  }

  public char userInput() {
    return Rogue.View.IO.getCh();
  }

  public char[][] getPrintChar() {
    return printChar;
  }
}
