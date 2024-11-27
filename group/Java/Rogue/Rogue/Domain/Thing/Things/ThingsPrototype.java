package Domain.Thing.Things;

import Domain.Thing.ThingEnums.*;

import java.util.Random;

public class ThingsPrototype {
  private Random random;

  public ThingsPrototype() {
    this.random = new Random();
  }

  public Thing createThing(int x, int y) {
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

    thing.setPosition(x, y);

    return thing;
  }
}
