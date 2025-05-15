package Rogue.Domain.Game.Control;

import java.util.ArrayList;
import java.util.Random;
import java.util.Iterator;
import java.util.List;

import Rogue.Domain.Game.Objects.Map;
import Rogue.Domain.Game.Objects.Character.Hero;
import Rogue.Domain.Game.Objects.Thing.Thing;
import Rogue.Domain.Game.Objects.Thing.ThingFabric;
import Rogue.Domain.Game.Utility.Position;

public class ThingList {
  private final ArrayList<Thing> things;
  private final Random rand;

  public ThingList(Random rand) {
    this.rand = rand;
    things = new ArrayList<>();
  }

  public void createThing(char[][] map, int floor, int checkHard) {
    int count = 5 + floor / 2 - checkHard * 2;

    for (int i = 0; i < count; i++) {
      Position emptySpace = getEmptySpace(map);
      things.add(ThingFabric.createThing(emptySpace, rand));
    }
  }

  private Position getEmptySpace(char[][] map) {
    int x, y;
    do {
      x = rand.nextInt(Map.MAP_WIDTH);
      y = rand.nextInt(Map.MAP_HEIGHT);
    } while (map[y][x] != '·');
    map[y][x] = 't';

    return new Position(x, y);
  }

  public List<Thing> getThingsList() {
    return things;
  }

  public void clearThingList() {
    things.clear();
  }

  public void getThings(Hero hero) {
    Iterator<Thing> iterator = things.iterator();
    while (iterator.hasNext()) {
      Thing thing = iterator.next();
      if (thing.getPosition().x() == hero.getPosition().x() && thing.getPosition().y() == hero.getPosition().y()) {
        hero.getBackpack().addItem(thing.getThingType(), thing.getThingSubType());
        iterator.remove();
      }
    }
  }
}