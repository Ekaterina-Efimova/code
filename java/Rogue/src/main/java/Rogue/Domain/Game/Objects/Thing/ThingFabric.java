package Rogue.Domain.Game.Objects.Thing;

import Rogue.Domain.Game.Objects.Thing.ThingEnums.*;
import Rogue.Domain.Game.Utility.Position;

import java.util.Random;

public class ThingFabric {
  private ThingFabric() {
  }

  public static Thing createThing(Position position, Random random) {
    ThingType type = ThingType.values()[random.nextInt(ThingType.values().length)];

    Thing thing = null;

    if (type == ThingType.Еда) {
      thing = new Thing(ThingType.Еда, OtherSubType.None);
    } else if (type == ThingType.Зелье) {
      thing = new Thing(ThingType.Зелье, ElixirSubType.values()[random.nextInt(ElixirSubType.values().length)]);
    } else if (type == ThingType.Свиток) {
      thing = new Thing(ThingType.Свиток, ScrollSubType.values()[random.nextInt(ScrollSubType.values().length)]);
    } else if (type == ThingType.Оружие) {
      thing = new Thing(ThingType.Оружие, WeaponSubType.values()[random.nextInt(WeaponSubType.values().length)]);
    }

    thing.setPosition(position);

    return thing;
  }
}