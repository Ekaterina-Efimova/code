package Rogue;

import Rogue.Controllers.ControllerGame;

public class App {
  public static void main(String[] args) {
    Rogue.View.IO.resetCmd();
    Rogue.View.IO.hideCursor();
    ControllerGame g = new ControllerGame();
    g.play();
    Rogue.View.IO.showCursor();
  }
}