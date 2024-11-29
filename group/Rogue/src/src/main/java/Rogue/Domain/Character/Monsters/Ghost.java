package Rogue.Domain.Character.Monsters;

import Rogue.Domain.Character.CharacterEnums.*;
import Rogue.Domain.Character.Control.Character;
import Rogue.Domain.Utility.Direction;

public class Ghost extends Character {
  public Ghost() {
    super(Health.LOW, Power.MEDIUM, Agitility.HIGH, Hostility.MEDIUM, Speed.SUPERHIGH);
    monsterName = (rand.nextBoolean()) ? 'G' : '·';
    this.room = null;
  }

  @Override
  public int attack(Character victim) {
    monsterName = 'G';
    return super.attack(victim);
  }

  @Override
  public boolean move(Direction direction) {
    getVision();
    return super.move(direction);
  }

  @Override
  public void idle() {
    super.idle();
    getVision();
    blink();
  }

  private void getVision() {
    monsterName = (rand.nextInt(7) == 0) ? 'G' : '·';
  }

  private void blink() {
    if (rand.nextInt(15) == 0) {
      int x = rand.nextInt(room.x2() - room.x1() - 1) + room.x1() + 1;
      int y = rand.nextInt(room.y2() - room.y1() - 1) + room.y1() + 1;
      position.setPosition(x, y);
    }
  }

  @Override
  public int getMonsterExp() {
    return (int) (super.getMonsterExp() * 1.5);
  }
}