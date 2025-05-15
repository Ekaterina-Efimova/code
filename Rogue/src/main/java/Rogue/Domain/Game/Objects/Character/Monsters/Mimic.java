package Rogue.Domain.Game.Objects.Character.Monsters;

import Rogue.Domain.Game.Objects.Character.Character;
import Rogue.Domain.Game.Objects.Character.CharacterEnums.*;

public class Mimic extends Character {

  public Mimic() {
    super(Health.MEDIUM, Power.MEDIUM, Agility.LOW, Hostility.LOW, Speed.LOW);
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