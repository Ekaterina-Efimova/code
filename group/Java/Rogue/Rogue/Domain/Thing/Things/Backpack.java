package Domain.Thing.Things;

import Domain.Thing.ThingEnums.*;

import java.util.HashMap;
import java.util.EnumMap;
import java.util.ArrayList;
import java.util.List;

public class Backpack {
  private EnumMap<ThingType, HashMap<ThingSubType, Integer>> backpack;

  public Backpack() {
    backpack = new EnumMap<>(ThingType.class);
    for (ThingType thingType : ThingType.values()) {
      HashMap<ThingSubType, Integer> typeMap = initializeTypeMap(thingType);
      backpack.put(thingType, typeMap);
    }
  }

  private HashMap<ThingSubType, Integer> initializeTypeMap(ThingType thingType) {
    HashMap<ThingSubType, Integer> typeMap = new HashMap<>();

    if (thingType == ThingType.Еда) {
      typeMap.put(OtherSubType.None, 0);
    } else if (thingType == ThingType.Зелье) {
      initializeTypeMap(typeMap, ElixirSubType.values());
    } else if (thingType == ThingType.Свиток) {
      initializeTypeMap(typeMap, ScrollSubType.values());
    } else if (thingType == ThingType.Оружие) {
      initializeTypeMap(typeMap, WeaponSubType.values());
    }

    return typeMap;
  }

  private void initializeTypeMap(HashMap<ThingSubType, Integer> typeMap, ThingSubType[] values) {
    for (ThingSubType subType : values) {
      typeMap.put(subType, 0);
    }
  }

  public void addItem(ThingType thingType, ThingSubType subType) {
    if (backpack.containsKey(thingType) && backpack.get(thingType).containsKey(subType)) {
      int count = backpack.get(thingType).get(subType);

      if (count < 9) {
        backpack.get(thingType).put(subType, count + 1);
      }
    }
  }

  public boolean removeItem(ThingType thingType, ThingSubType subType) {
    boolean removed = false;
    if (backpack.containsKey(thingType) && backpack.get(thingType).containsKey(subType)) {
      int count = backpack.get(thingType).get(subType);

      if (count > 0) {
        backpack.get(thingType).put(subType, count - 1);
        removed = true;
      }
    }
    return removed;
  }

  public int getItemCount(ThingType thingType, ThingSubType subType) {
    int count = -1;

    if (backpack.containsKey(thingType) && backpack.get(thingType).containsKey(subType))
      count = backpack.get(thingType).get(subType);

    return count;
  }

  public List<Thing> getThings() {
    List<Thing> things = new ArrayList<>();
    for (ThingType thingType : ThingType.values()) {
      for (ThingSubType subType : backpack.get(thingType).keySet()) {
        if (backpack.get(thingType).get(subType) > 0) {
          things.add(new Thing(thingType, subType));
        }
      }
    }
    return things;
  }

  public List<ThingSubType> getThings(ThingType thingType) {
    List<ThingSubType> things = new ArrayList<>();
    for (ThingSubType subType : backpack.get(thingType).keySet())
      if (backpack.get(thingType).get(subType) > 0)
        things.add(subType);
    return things;
  }

  public EnumMap<ThingType, HashMap<ThingSubType, Integer>> getBackpack() {
    return backpack;
  }
}
