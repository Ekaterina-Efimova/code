package Domain.Character.Monsters;

import Domain.Character.CharacterEnums.*;
import Domain.Character.Control.Character;

public class Ogre extends Character {
  private boolean canAttack;

  public Ogre() {
    super(Health.SUPERHIGH, Power.SUPERHIGH, Agitility.LOW, Hostility.HIGH, Speed.MEDIUM);
    this.monsterName = 'O';
    this.canAttack = true;
  }

  @Override
  public int getMonsterExp() {
    return 5;
  }

  @Override
  public int attack(Character target) {
    int damage = 0;

    if (canAttack) {
      canAttack = false;
      damage = super.attack(target);
    } else {
      canAttack = true;
    }

    return damage;
  }
}
