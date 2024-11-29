package Rogue.Domain.Character.Monsters;

import Rogue.Domain.Character.CharacterEnums.*;
import Rogue.Domain.Character.Control.Character;

public class Ogre extends Character {
  private boolean canAttack;

  public Ogre() {
    super(Health.SUPERHIGH, Power.SUPERHIGH, Agitility.LOW, Hostility.HIGH, Speed.MEDIUM);
    this.monsterName = 'O';
    this.canAttack = true;
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