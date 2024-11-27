package Domain.Character.Monsters;

import Domain.Character.CharacterEnums.*;
import Domain.Character.Control.Character;
import Domain.Utility.Direction;

//отображение: белая s
//Ходит по карте по диагоналям, постоянно меняя сторону. 
//У каждой успешной атаки есть вероятность «усыпить» игрока на один ход.
public class SnakeMage extends Character {
  public SnakeMage() {
    super(Health.MEDIUM, Power.MEDIUM, Agitility.SUPERHIGH, Hostility.HIGH, Speed.HIGH);
    monsterName = 'S';
  }

  @Override
  public boolean move(Direction direction) { // пробный вариант
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

  @Override
  public int getMonsterExp() {
    return 3;
  }
}