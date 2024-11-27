package Domain.Character.Monsters;

import Domain.Character.CharacterEnums.*;
import Domain.Character.Control.Character;
import Domain.Utility.Direction;

public class Ghost extends Character {
  public Ghost() {
    super(Health.LOW, Power.MEDIUM, Agitility.HIGH, Hostility.LOW, Speed.SUPERHIGH);
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
    if (rand.nextInt(10) == 0) {
      blink();
    }
  }

  private void getVision() {
    monsterName = (rand.nextInt(5) == 0) ? 'G' : '·';
  }

  private void blink() {
    int x = rand.nextInt(room.x2() - room.x1() - 1) + room.x1() + 1;
    int y = rand.nextInt(room.y2() - room.y1() - 1) + room.y1() + 1;
    position.setPosition(x, y);
  }

  @Override
  public int getMonsterExp() {
    return 3;
  }
}