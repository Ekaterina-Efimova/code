package Rogue.Domain.Character.Monsters;

import Rogue.Domain.Character.CharacterEnums.*;
import Rogue.Domain.Character.Control.Character;

public class Mimic extends Character {

  public Mimic() {
    super(Health.MEDIUM, Power.MEDIUM, Agitility.LOW, Hostility.LOW, Speed.LOW);
    monsterName = 't';
  }

  @Override
  public void idle() {
    monsterName = 't';
    super.idle();
  }

  @Override
  public int getMonsterExp() {
    return (int) (super.getMonsterExp() * 1.5);
  }

  @Override
  public int attack(Character victim) {
    monsterName = 'M';
    return super.attack(victim);
  }
}