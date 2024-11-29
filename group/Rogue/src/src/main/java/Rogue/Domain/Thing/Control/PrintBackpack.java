package Rogue.Domain.Thing.Control;

import Rogue.Domain.Character.Control.Hero;
import Rogue.Domain.Game.Objects.Map;
import Rogue.Domain.Thing.ThingEnums.*;
import Rogue.Domain.Thing.Things.Backpack;

import java.util.List;

public class PrintBackpack {
  private Backpack backpack;

  public PrintBackpack(Hero hero) {
    this.backpack = hero.getBackpack();
  }

  public void setBackpack(Hero hero) {
    this.backpack = hero.getBackpack();
  }

  public void printOneType(char c, char[][] print) {
    ThingType thingType = ThingType.parseThingType(c);
    if (thingType != null) {
      printThings(print, thingType);
    }
  }

  private void printThings(char[][] printChar, ThingType thingType) {
    printChar[Map.MAP_HEIGHT + 2] = createStringInventory(thingType).toCharArray();
  }

  private String createStringInventory(ThingType thingType) {
    List<ThingSubType> things = backpack.getThings(thingType);
    StringBuilder sb = new StringBuilder();

    if (thingType == ThingType.Еда) {
      int count = backpack.getItemCount(ThingType.Еда, OtherSubType.None);
      sb.append(String.format("1) %s: %d", thingType, count));

    } else {
      sb.append(String.format("%s:", thingType));
      for (ThingSubType thing : things) {
        int count = backpack.getItemCount(thingType, thing);
        sb.append(String.format("%n%d) %s: %d", thing.getOrder(), thing, count));
      }
    }

    return sb.toString();
  }

  public void printInventory(char[][] printChar) {
    printChar[Map.MAP_HEIGHT + 2] = printBackpackThingType().toCharArray();
  }

  public String printBackpackThingType() {
    StringBuilder sb = new StringBuilder("Инвентарь: ");

    for (ThingType thingType : ThingType.values()) {
      char ch = getChar(thingType);

      sb.append(String.format("%n%c) %s", ch, thingType));

      if (thingType == ThingType.Еда)
        sb.append(String.format(" - количество: %d", backpack.getItemCount(thingType, OtherSubType.None)));

      else {
        int count = 0;
        for (ThingSubType subType : backpack.getBackpack().get(thingType).keySet())
          count += backpack.getItemCount(thingType, subType);
        sb.append(String.format(" - количество: %d", count));
      }
    }

    return sb.toString();
  }

  private char getChar(ThingType thingType) {
    char ch = 'h';
    if (thingType == ThingType.Еда) {
      ch = 'j';
    } else if (thingType == ThingType.Зелье) {
      ch = 'k';
    } else if (thingType == ThingType.Свиток) {
      ch = 'e';
    }

    return ch;
  }
}