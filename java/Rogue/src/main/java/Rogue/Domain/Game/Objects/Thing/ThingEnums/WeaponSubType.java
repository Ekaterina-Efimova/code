package Rogue.Domain.Game.Objects.Thing.ThingEnums;

public enum WeaponSubType implements ThingSubType {
  Булава,
  ОдноручныйМеч,
  Кинжал,
  ДвуручныйМеч,
  Копье;

  @Override
  public int getOrder() {
    return ordinal() + 1;
  }

  public static WeaponSubType parseWeaponSubType(char c) {
    int order = c - '0';
    return getByOrder(order);
  }

  private static WeaponSubType getByOrder(int item) {
    for (WeaponSubType subType : values()) {
      if (subType.getOrder() == item) {
        return subType;
      }
    }
    return null;
  }
}