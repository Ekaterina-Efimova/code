package Rogue.Domain.Game.Utility;

public class Position {
  int x;
  int y;

  public Position(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public Position() {
    this(0, 0);
  }

  public void setPosition(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public int x() {
    return x;
  }

  public int y() {
    return y;
  }
}