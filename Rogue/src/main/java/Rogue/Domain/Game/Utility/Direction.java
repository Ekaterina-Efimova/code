package Rogue.Domain.Game.Utility;

public enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT;

  public static Direction get(char c) {
    Direction dir;
    if (c == 'w' || c == '\u0041') {
      dir = Direction.UP;
    } else if (c == 's' || c == '\u0042') {
      dir = Direction.DOWN;
    } else if (c == 'a' || c == '\u0044') {
      dir = Direction.LEFT;
    } else if (c == 'd' || c == '\u0043') {
      dir = Direction.RIGHT;
    } else {
      dir = null;
    }
    return dir;
  }

  public static Direction getOpposite(Direction direction) {
    if (direction == Direction.UP) {
      direction = Direction.DOWN;
    } else if (direction == Direction.DOWN) {
      direction = Direction.UP;
    } else if (direction == Direction.LEFT) {
      direction = Direction.RIGHT;
    } else if (direction == Direction.RIGHT) {
      direction = Direction.LEFT;
    }

    return direction;
  }
}