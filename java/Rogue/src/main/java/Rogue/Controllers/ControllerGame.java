package Rogue.Controllers;

import Rogue.Domain.Game.Control.GameData;
import Rogue.Domain.Game.Utility.PrePrint.PrePrint;

public class ControllerGame {
  private final ControllerView controllerView;
  private char lastC;
  private final GameData game;

  public ControllerGame() {
    controllerView = new ControllerView();
    lastC = ' ';
    game = GameData.getInstance();
  }

  public void play() {
    controllerView.printFirstScreen();
    askGameLoadChoice();

    do {
      game();
    } while (userInput() != 'q' && game.gameInProgress());

    if (!game.gameInProgress())
      ControllerDatalayer.saveGame();
    controllerView.printEndLogo();
  }

  private void game() {
    PrePrint.sendAllInfo(controllerView.getPrintChar());
    controllerView.draw();
  }

  private void askGameLoadChoice() {
    char c = controllerView.getNewGameChoice();

    ControllerDatalayer.loadGame();
    if (c == 'n' || c == 'N') {
      game.getHero().setName(controllerView.printHeroName());
    } else {
      game.loadHero();
    }
  }

  private char userInput() {
    char c = controllerView.userInput();

    game.moveHero(c);
    game.backpack(c, lastC);
    lastC = c;

    return c;
  }
}