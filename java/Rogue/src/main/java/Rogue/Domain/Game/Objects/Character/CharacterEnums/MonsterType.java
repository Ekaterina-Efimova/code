package Rogue.Domain.Game.Objects.Character.CharacterEnums;

import java.util.Random;

public enum MonsterType {
  ZOMBIE,
  VAMPIRE,
  GHOST,
  OGRE,
  SNAKE_MAGE,
  MIMIC;

  private static final Random RANDOM = new Random();

  public static MonsterType random() {
    return values()[RANDOM.nextInt(values().length)];
  }
}