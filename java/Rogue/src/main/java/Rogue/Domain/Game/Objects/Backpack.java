package Rogue.Domain.Game.Objects;

import java.util.HashMap;
import java.util.EnumMap;
import java.util.Map;

import Rogue.Domain.Game.Objects.Thing.ThingEnums.*;

import java.util.ArrayList;
import java.util.List;

public class Backpack {
  private final EnumMap<ThingType, HashMap<ThingSubType, Integer>> items;

  public Backpack() {
    items = new EnumMap<>(ThingType.class);
    for (ThingType thingType : ThingType.values()) {
      HashMap<ThingSubType, Integer> typeMap = initializeTypeMap(thingType);
      items.put(thingType, typeMap);
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
    if (items.containsKey(thingType) && items.get(thingType).containsKey(subType)) {
      int count = items.get(thingType).get(subType);

      if (count < 9) {
        items.get(thingType).put(subType, count + 1);
      }
    }
  }

  public boolean removeItem(ThingType thingType, ThingSubType subType) {
    boolean removed = false;
    if (items.containsKey(thingType) && items.get(thingType).containsKey(subType)) {
      int count = items.get(thingType).get(subType);

      if (count > 0) {
        items.get(thingType).put(subType, count - 1);
        removed = true;
      }
    }
    return removed;
  }

  public int getItemCount(ThingType thingType, ThingSubType subType) {
    int count = -1;

    if (items.containsKey(thingType) && items.get(thingType).containsKey(subType))
      count = items.get(thingType).get(subType);

    return count;
  }

  public List<ThingSubType> getThings(ThingType thingType) {
    List<ThingSubType> things = new ArrayList<>();
    for (ThingSubType subType : items.get(thingType).keySet())
      if (items.get(thingType).get(subType) > 0)
        things.add(subType);
    return things;
  }

  public Map<ThingType, HashMap<ThingSubType, Integer>> getItems() {
    return items;
  }
}