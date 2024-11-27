package Controllers;

import Domain.Game.Control.PrintMap;
import Domain.Game.Objects.Map;
import Domain.Utility.Direction;
import View.Logo;

public class ControllerGame {
  private char[][] printChar;
  private PrintMap printMap;
  private Logo logo;
  private ContollerDatalayer controllerDatalayer;

  public ControllerGame() {
    printMap = new PrintMap();
    printChar = new char[Map.MAP_HEIGHT + 3][100];
    logo = new Logo(printChar);
    controllerDatalayer = new ContollerDatalayer();
  }

  public void play() {
    logo.printFirstScreen();
    askGameLoadChoice();
    do {
      draw();
      controllerDatalayer.saveGame(printMap);
    } while (userInput() != 'q' && printMap.heroAlive());

    controllerDatalayer.saveGame(printMap);
    logo.printEndLogo(printMap);
  }

  private void askGameLoadChoice() {
    char c = View.IO.getCh();
    if (c != 'n' && c != 'N') {
      controllerDatalayer.loadGame(printMap);
    } else {
      String heroName = askName();
      printMap.getPlayer().setName(heroName);
      clearPrintChar();
      printChar[0] = String.format(" Welcome, %s", heroName).toCharArray();
    }
  }

  private String askName() {
    printChar[Map.MAP_HEIGHT + 2] = "Введите имя героя: ".toCharArray();
    View.IO.print(printChar);
    return View.IO.getString();
  }

  private char userInput() {
    char c = View.IO.getCh();
    Direction dir = Direction.get(c);

    if (dir != null) {
      printMap.movePlayer(dir, printChar);
    } else {
      printMap.backpack(c, printChar);
    } 

    return c;
  }

  private void draw() {
    printMap.sendAllInfo(printChar);
    View.IO.print(printChar);
    clearPrintChar();
  }

  private void clearPrintChar() {
    printChar[Map.MAP_HEIGHT + 2] = "".toCharArray();
  }

  // private void saveGame() {
  //   if (printMap.isNewFloor()) {
  //     controllerDatalayer.saveGame(printMap);
  //     printMap.setNewFloor(false);
  //   }

  //   if (!printMap.heroAlive()) {
  //     controllerDatalayer.returnStatistics(printMap);
  //     controllerDatalayer.saveGame(printMap);
  //   }
  // }
}