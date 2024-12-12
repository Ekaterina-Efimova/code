package Rogue.Domain.Game.Utility.PrePrint;

import Rogue.Domain.Game.Objects.Thing.ThingEnums.ThingType;

public enum InventoryToPrint {
  NONE, ALL, Оружие, Свиток, Еда, Зелье;

  public static InventoryToPrint get(char c) {
    InventoryToPrint result;
    ThingType thingType = ThingType.parseThingType(c);

    if (c == 'i' || c == 'I') {
      result = ALL;
    } else if (thingType != null) {
      result = InventoryToPrint.valueOf(thingType.name());
    } else {
      result = NONE;
    }

    return result;
  }
}
