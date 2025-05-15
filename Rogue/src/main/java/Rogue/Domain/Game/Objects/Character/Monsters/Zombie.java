package Rogue.Domain.Game.Objects.Character.Monsters;

import Rogue.Domain.Game.Objects.Character.Character;
import Rogue.Domain.Game.Objects.Character.CharacterEnums.*;

public class Zombie extends Character {
  public Zombie() {
    super(Health.HIGH, Power.MEDIUM, Agility.LOW, Hostility.MEDIUM, Speed.LOW);
    this.monsterName = 'Z';
  }
}