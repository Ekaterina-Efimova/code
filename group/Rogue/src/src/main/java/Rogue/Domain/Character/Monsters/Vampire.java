package Rogue.Domain.Character.Monsters;

import Rogue.Domain.Character.CharacterEnums.*;
import Rogue.Domain.Character.Control.Character;

public class Vampire extends Character {
  private boolean firstAttack;

  public Vampire() {
    super(Health.MEDIUM, Power.MEDIUM, Agitility.HIGH, Hostility.HIGH, Speed.MEDIUM);
    this.monsterName = 'V';
    this.firstAttack = true;
  }

  @Override
  public int getMonsterExp() {
    return (int) (super.getMonsterExp() * 1.5);
  }

  public boolean isFirstAttack() {
    return firstAttack;
  }

  public void setFirstAttack(boolean firstAttack) {
    this.firstAttack = firstAttack;
  }
}