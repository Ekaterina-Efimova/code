package Rogue.Domain.Game.Objects.Thing.ThingEnums;

public enum ThingType {
  Еда,
  Зелье,
  Свиток,
  Оружие;

  public static ThingType parseThingType(char c) {
    ThingType thingType = null;

    if (c == 'h') {
      thingType = ThingType.Оружие;
    } else if (c == 'j') {
      thingType = ThingType.Еда;
    } else if (c == 'k') {
      thingType = ThingType.Зелье;
    } else if (c == 'e') {
      thingType = ThingType.Свиток;
    }

    return thingType;
  }
}