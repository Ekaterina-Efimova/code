package Domain.Character.CharacterEnums;

public enum Agitility {
  LOW(2),
  MEDIUM(4),
  HIGH(8),
  SUPERHIGH(16);

  private final int value;

  Agitility(int value) {
    this.value = value;
  }

  public int getValue() {
    return value;
  }
}
