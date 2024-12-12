package Rogue.Domain.Game.Utility.PrePrint;

import Rogue.Domain.Game.Control.GameData;
import Rogue.Domain.Game.Objects.Backpack;
import Rogue.Domain.Game.Objects.Map;
import Rogue.Domain.Game.Objects.Thing.ThingEnums.*;

import java.util.List;

public class PrePrintBackpack {
  private PrePrintBackpack() {
  }

  public static void printBackpack(char[][] printChar) {
    InventoryToPrint type = GameData.getInstance().getInventoryToPrint();

    if (type == InventoryToPrint.ALL) {
      printAllTypes(printChar);
    } else if (type != InventoryToPrint.NONE) {
      printOneType(printChar, type);
    } else {
      printChar[Map.MAP_HEIGHT + 2] = "".toCharArray();
    }
  }

  private static void printOneType(char[][] printChar, InventoryToPrint type) {
    ThingType thingType = ThingType.valueOf(type.name());
    printChar[Map.MAP_HEIGHT + 2] = createStringInventory(thingType).toCharArray();
  }

  private static String createStringInventory(ThingType thingType) {
    Backpack backpack = GameData.getInstance().getHero().getBackpack();
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

  private static void printAllTypes(char[][] printChar) {
    printChar[Map.MAP_HEIGHT + 2] = printBackpackThingType().toCharArray();
  }

  private static String printBackpackThingType() {
    Backpack backpack = GameData.getInstance().getHero().getBackpack();
    StringBuilder sb = new StringBuilder("Инвентарь: ");

    for (ThingType thingType : ThingType.values()) {
      char ch = getChar(thingType);

      sb.append(String.format("%n%c) %s", ch, thingType));

      if (thingType == ThingType.Еда)
        sb.append(String.format(" - количество: %d", backpack.getItemCount(thingType, OtherSubType.None)));

      else {
        int count = 0;
        for (ThingSubType subType : backpack.getItems().get(thingType).keySet())
          count += backpack.getItemCount(thingType, subType);
        sb.append(String.format(" - количество: %d", count));
      }
    }

    return sb.toString();
  }

  private static char getChar(ThingType thingType) {
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