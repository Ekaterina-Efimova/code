package Domain.Character.Monsters;

import Domain.Character.CharacterEnums.*;
import Domain.Character.Control.Character;

public class Zombie extends Character {
  public Zombie() {
    super(Health.HIGH, Power.MEDIUM, Agitility.LOW, Hostility.MEDIUM, Speed.LOW);
    this.monsterName = 'Z';
  }

  @Override
  public int getMonsterExp() {
    return 2;
  }
}