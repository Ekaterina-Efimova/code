package Rogue.Domain.Game.Objects.Character.Monsters;

import Rogue.Domain.Game.Objects.Character.Character;
import Rogue.Domain.Game.Objects.Character.CharacterEnums.*;

public class Ogre extends Character {
  private boolean canAttack;

  public Ogre() {
    super(Health.SUPERHIGH, Power.SUPERHIGH, Agility.LOW, Hostility.HIGH, Speed.MEDIUM);
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