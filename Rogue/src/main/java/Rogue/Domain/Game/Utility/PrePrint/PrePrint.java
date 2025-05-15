package Rogue.Domain.Game.Utility.PrePrint;

import java.util.List;

import Rogue.Domain.Game.Control.GameData;
import Rogue.Domain.Game.Objects.Map;
import Rogue.Domain.Game.Objects.Character.Character;
import Rogue.Domain.Game.Objects.Character.Hero;
import Rogue.Domain.Game.Objects.Thing.Thing;

public class PrePrint {
  private static GameData game;
  private static char[][] printChar;

  private PrePrint() {
  }

  public static void sendAllInfo(char[][] input) {
    game = GameData.getInstance();
    printChar = input;
    sendTurnDescription();
    sendMap();
    sendStats();
    PrePrintBackpack.printBackpack(printChar);
  }

  private static void sendTurnDescription() {
    printChar[0] = game.getTurnDescription().toCharArray();
  }

  private static void sendMap() {
    char[][] map = game.getTempMap();
    copyMap();
    sendUnits();

    boolean[][] fogOfWar = game.getFogOfWar();
    for (int y = 0; y < Map.MAP_HEIGHT; y++) {
      for (int x = 0; x < Map.MAP_WIDTH; x++) {
        if (fogOfWar[y][x]) {
          printChar[y + 1][x] = ' ';
        } else {
          printChar[y + 1][x] = map[y][x];
        }
      }
    }
  }

  private static void sendUnits() {
    game.getTempMap()[game.getHero().getPosition().y()][game.getHero().getPosition().x()] = '@';
    sendMonsters();
    sendThings();
  }

  private static void sendMonsters() {
    List<Character> monsters = game.getMonsters();
    for (Character monster : monsters) {
      int monsterX = monster.getPosition().x();
      int monsterY = monster.getPosition().y();

      game.getTempMap()[monsterY][monsterX] = monster.getMonsterName();
    }
  }

  private static void sendThings() {
    List<Thing> things = game.getThings();
    for (Thing thing : things) {
      int thingX = thing.getPosition().x();
      int thingY = thing.getPosition().y();

      game.getTempMap()[thingY][thingX] = thing.getThingName();
    }
  }

  private static void sendStats() {
    Hero hero = game.getHero();
    String s = String.format(
        "Этаж: %2d Золото: %6d Здоровье(макс): %3d(%3d) Сила: %2d Ловкость: %2d Уровень/Опыт: %2d/ %7d",
        game.getHero().getFloor(), hero.getGold(), hero.getHealth(), hero.getMaxHealth(),
        hero.getPower(), hero.getAgility(), hero.getLevel(), hero.getExp());

    printChar[Map.MAP_HEIGHT + 1] = s.toCharArray();
  }

  private static void copyMap() {
    for (int y = 0; y < Map.MAP_HEIGHT; y++) {
      System.arraycopy(game.getAsciiMap()[y], 0, game.getTempMap()[y], 0, Map.MAP_WIDTH);
    }
  }
}