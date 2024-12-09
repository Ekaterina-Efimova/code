package Rogue.Domain.Thing.Control;

import java.util.ArrayList;
import java.util.Random;
import java.util.Iterator;
import java.util.List;

import Rogue.Domain.Character.Control.Hero;
import Rogue.Domain.Game.Objects.Map;
import Rogue.Domain.Thing.Things.ThingsPrototype;
import Rogue.Domain.Utility.Position;
import Rogue.Domain.Thing.Things.Thing;

public class ThingList {
  private ArrayList<Thing> things;
  private ThingsPrototype thingsPrototype;
  private Random rand;

  public ThingList(Random rand) {
    this.rand = rand;
    things = new ArrayList<>();
    thingsPrototype = new ThingsPrototype();
  }

  public void createThing(char[][] map, int floor, int checkHard) {
    int count = 5 + floor / 2 - checkHard * 2;

    for (int i = 0; i < count; i++) {
      Position emptySpace = getEmptySpace(map);
      things.add(thingsPrototype.createThing(emptySpace));
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

  public void addThing(Thing thing) {
    things.add(thing);
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