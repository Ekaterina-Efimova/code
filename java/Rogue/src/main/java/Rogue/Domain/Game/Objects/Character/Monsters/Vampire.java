package Rogue.Domain.Game.Objects.Character.Monsters;

import Rogue.Domain.Game.Objects.Character.Character;
import Rogue.Domain.Game.Objects.Character.CharacterEnums.*;

public class Vampire extends Character {
  private boolean firstAttack;

  public Vampire() {
    super(Health.MEDIUM, Power.MEDIUM, Agility.HIGH, Hostility.HIGH, Speed.MEDIUM);
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