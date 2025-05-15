package Rogue.Domain.Game.Objects.Thing.ThingEnums;

public interface ThingSubType {
  int getOrder();

  static ThingSubType parseThingSubType(ThingType thingType, char c) {
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