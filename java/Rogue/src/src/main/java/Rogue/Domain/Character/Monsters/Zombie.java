package Rogue.Domain.Character.Monsters;

import Rogue.Domain.Character.CharacterEnums.*;
import Rogue.Domain.Character.Control.Character;

public class Zombie extends Character {
  public Zombie() {
    super(Health.HIGH, Power.MEDIUM, Agitility.LOW, Hostility.MEDIUM, Speed.LOW);
    this.monsterName = 'Z';
  }
}