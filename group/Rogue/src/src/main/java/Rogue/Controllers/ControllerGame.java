package Rogue.Controllers;

import Rogue.Domain.Game.Control.PrePrint;

public class ControllerGame {
  private PrePrint prePrint;
  private ContollerDatalayer controllerDatalayer;
  private ControllerView controllerView;

  public ControllerGame() {
    controllerView = new ControllerView();
    controllerDatalayer = new ContollerDatalayer();
  }

  public void play() {
    controllerView.printFirstScreen();
    askGameLoadChoice();

    do {
      game();
    } while (userInput() != 'q' && prePrint.heroAlive());

    controllerDatalayer.saveGame(prePrint);
    controllerView.printEndLogo(prePrint.heroAlive(), prePrint.getFloor() == 21, controllerDatalayer.getGameStatistic());
  }

  private void game() {
    prePrint.sendAllInfo(controllerView.getPrintChar());
    controllerView.draw();
    controllerDatalayer.saveGame(prePrint);
  }

  private void askGameLoadChoice() {
    char c = controllerView.getGame();
    prePrint = controllerDatalayer.loadGame();
 
    if (c == 'n' || c == 'N' || prePrint == null) {
      prePrint = new PrePrint(null);
      prePrint.getPlayer().setName(controllerView.printHeroName());
    }
  }

  private char userInput() {
    char c = controllerView.userInput();

    prePrint.movePlayer(c, controllerView.getPrintChar());
    prePrint.backpack(c, controllerView.getPrintChar());

    return c;
  }
}