package Rogue.Domain.Thing.ThingEnums;

public interface ThingSubType {
  public int getOrder();

  public static ThingSubType parseThingSubType(ThingType thingType, char c) {
    ThingSubType subType = OtherSubType.None;

    if (thingType == ThingType.Зелье) {
      subType = ElixirSubType.parseElixirSubType(c);
    } else if (thingType == ThingType.Свиток) {
      subType = ScrollSubType.parseScrollSubType(c);
    } else if (thingType == ThingType.Оружие) {
      subType = WeaponSubType.parseWeaponSubType(c);
    }

    return subType;
  }
}