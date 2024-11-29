package Rogue.Domain.Game.Control;

import java.util.List;

import Rogue.Domain.Thing.Control.PrintBackpack;
import Rogue.Domain.Thing.Things.Thing;
import Rogue.Domain.Utility.Direction;
import Rogue.Domain.Character.Control.Character;
import Rogue.Domain.Character.Control.Hero;
import Rogue.Domain.Game.Objects.Map;
import Rogue.Domain.Game.Objects.MapControl;

public class PrePrint {
  private MapControl mapControl;
  private PrintBackpack printBackpack;
  private char lastC;

  public PrePrint(Hero hero) {
    mapControl = new MapControl(hero == null ? new Hero() : hero);
    printBackpack = new PrintBackpack(mapControl.getPlayer());
    lastC = ' ';
  }

  public boolean heroAlive() {
    return mapControl.getPlayer().getHealth() > 0 && mapControl.getFloor() <= 21;
  }

  public void movePlayer(char c, char[][] printChar) {
    Direction dir = Direction.get(c);

    if (dir != null)
      mapControl.movePlayer(dir, printChar);
  }

  public void backpack(char c, char[][] printChar) {
    if (c >= '1' && c <= '9') {
      useThing(c, lastC, printChar);
    } else if (c == 'i' || c == 'I') {
      printBackpack.printInventory(printChar);
    } else {
      printBackpack.printOneType(c, printChar);
    }

    lastC = c;
  }

  public void useThing(char c, char lastC, char[][] printChar) {
    printChar[0] = mapControl.chooseBunsType(c, lastC).toCharArray();
  }

  public void sendAllInfo(char[][] printChar) {
    sendMap(printChar);
    sendStats(printChar);
  }

  private void sendMap(char[][] printChar) {
    copyMap();
    sendUnits();

    boolean[][] fogOfWar = mapControl.getFogOfWar();
    for (int y = 0; y < Map.MAP_HEIGHT; y++) {
      for (int x = 0; x < Map.MAP_WIDTH; x++) {
        if (fogOfWar[y][x]) {
          printChar[y + 1][x] = ' ';
        } else {
          printChar[y + 1][x] = mapControl.getTempMap()[y][x];
        }
      }
    }
  }

  private void sendUnits() {
    mapControl.getTempMap()[mapControl.getPlayer().getPosition().y()][mapControl.getPlayer().getPosition().x()] = '@';
    sendMonsters();
    sendThings();
  }

  private void sendMonsters() {
    List<Character> monsters = mapControl.getMonsterList().getMonsters();
    for (Character monster : monsters) {
      int monsterX = monster.getPosition().x();
      int monsterY = monster.getPosition().y();

      mapControl.getTempMap()[monsterY][monsterX] = monster.getMonsterName();
    }
  }

  private void sendThings() {
    List<Thing> things = mapControl.getThingList().getThingsList();
    for (Thing thing : things) {
      int thingX = thing.getPosition().x();
      int thingY = thing.getPosition().y();

      mapControl.getTempMap()[thingY][thingX] = thing.getThingName();
    }
  }

  private void sendStats(char[][] printChar) {
    Hero hero = mapControl.getPlayer();
    String s = String.format(
        "Этаж: %2d Золото: %6d Здоровье(макс): %3d(%3d) Сила: %2d Ловкость: %2d Уровень/Опыт: %2d/ %7d",
        mapControl.getFloor(), hero.getGold(), hero.getHealth(), hero.getMaxHealth(),
        hero.getPower(), hero.getAgility(), hero.getLevel(), hero.getExp());

    printChar[Map.MAP_HEIGHT + 1] = s.toCharArray();
  }

  private void copyMap() {
    for (int y = 0; y < Map.MAP_HEIGHT; y++) {
      System.arraycopy(mapControl.getAsciiMap()[y], 0, mapControl.getTempMap()[y], 0, Map.MAP_WIDTH);
    }
  }

  public boolean isNewFloor() {
    return mapControl.isNewFloor();
  }

  public int getFloor() {
    return mapControl.getFloor();
  }

  public Hero getPlayer() {
    return mapControl.getPlayer();
  }

  public void setPlayer(Hero player) {
    mapControl.setPlayer(player);
  }

  public void setFloor(int floor) {
    mapControl.setFloor(floor);
  }
}