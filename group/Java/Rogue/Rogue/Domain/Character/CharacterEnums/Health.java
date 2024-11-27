package Domain.Character.CharacterEnums;

public enum Health {
  LOW(12),
  MEDIUM(30),
  HIGH(60),
  SUPERHIGH(150);

  private final int value;

  Health(int value) {
    this.value = value;
  }

  public int getValue() {
    return value;
  }
}
