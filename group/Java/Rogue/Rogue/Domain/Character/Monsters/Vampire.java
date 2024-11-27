package Domain.Character.Monsters;

import Domain.Character.CharacterEnums.*;
import Domain.Character.Control.Character;

public class Vampire extends Character {
  private boolean firstAttack;

  public Vampire() {
    super(Health.HIGH, Power.MEDIUM, Agitility.HIGH, Hostility.HIGH, Speed.MEDIUM);
    this.monsterName = 'V';
    this.firstAttack = true;
  }

  @Override
  public int getMonsterExp() {
    return 3;
  }

  public boolean isFirstAttack() {
    return firstAttack;
  }

  public void setFirstAttack(boolean firstAttack) {
    this.firstAttack = firstAttack;
  }
}