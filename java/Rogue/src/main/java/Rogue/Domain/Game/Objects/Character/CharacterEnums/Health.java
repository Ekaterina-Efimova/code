package Rogue.Domain.Game.Objects.Character.CharacterEnums;

public enum Health {
  LOW(20),
  MEDIUM(40),
  HIGH(70),
  SUPERHIGH(120);

  private final int value;

  Health(int value) {
    this.value = value;
  }

  public int getValue() {
    return value;
  }
}