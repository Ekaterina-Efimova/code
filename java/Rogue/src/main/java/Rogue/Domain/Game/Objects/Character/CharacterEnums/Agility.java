package Rogue.Domain.Game.Objects.Character.CharacterEnums;

public enum Agility {
  LOW(2),
  MEDIUM(4),
  HIGH(8),
  SUPERHIGH(16);

  private final int value;

  Agility(int value) {
    this.value = value;
  }

  public int getValue() {
    return value;
  }
}