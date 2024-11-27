package Rogue;

import Controllers.ControllerGame;

public class App {
  public static void main(String[] args) {
    View.IO.resetCmd();
    View.IO.hideCursor();
    ControllerGame g = new ControllerGame();
    g.play();
    View.IO.showCursor();
  }
}