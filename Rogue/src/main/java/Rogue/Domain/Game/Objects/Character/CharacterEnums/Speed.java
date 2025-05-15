package Rogue.Domain.Game.Objects.Character.CharacterEnums;

public enum Speed {
  LOW(1),
  MEDIUM(2),
  HIGH(3),
  SUPERHIGH(4);

  private final int value;

  Speed(int value) {
    this.value = value;
  }

  public int getValue() {
    return value;
  }
}