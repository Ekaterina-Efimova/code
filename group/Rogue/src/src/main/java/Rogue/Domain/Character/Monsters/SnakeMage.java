package Rogue.Domain.Character.Monsters;

import Rogue.Domain.Character.CharacterEnums.*;
import Rogue.Domain.Character.Control.Character;
import Rogue.Domain.Utility.Direction;

public class SnakeMage extends Character {
  public SnakeMage() {
    super(Health.MEDIUM, Power.MEDIUM, Agitility.SUPERHIGH, Hostility.HIGH, Speed.HIGH);
    monsterName = 'S';
  }

  @Override
  public boolean move(Direction direction) {
    hostility = 4;
    boolean moved = true;

    if (direction == Direction.UP) {
      move(-1, -1);
    } else if (direction == Direction.DOWN) {
      move(1, 1);
    } else if (direction == Direction.LEFT) {
      move(-1, 1);
    } else if (direction == Direction.RIGHT) {
      move(1, -1);
    } else {
      moved = false;
    }

    int x = position.x();
    if (x <= room.x1()) {
      move(2, 0);
    } else if (x >= room.x2()) {
      move(-2, 0);
    }
    int y = position.y();
    if (y <= room.y1()) {
      move(0, 2);
    } else if (y >= room.y2()) {
      move(0, -2);
    }

    return moved;
  }
}