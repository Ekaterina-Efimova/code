package Rogue.Domain.Game.Utility;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import Rogue.Domain.Game.Control.GameData;
import Rogue.Domain.Game.Objects.Map;
import Rogue.Domain.Game.Objects.Character.Character;
import Rogue.Domain.Game.Objects.Character.Hero;
import Rogue.Domain.Game.Objects.Thing.Thing;
import Rogue.Domain.Game.Objects.Thing.ThingEnums.*;

public class Buns {
  private static final Random random = new Random();
  private static GameData game;
  private static Hero hero;

  private Buns() {
  }

  public static void useThing(char c, char lastC) {
    game = GameData.getInstance();
    hero = game.getHero();
    ThingType thingType = ThingType.parseThingType(lastC);
    ThingSubType thingSubType = ThingSubType.parseThingSubType(thingType, c);

    if (thingType != null && thingSubType != null)
      getBuns(thingType, thingSubType);
  }

  private static void getBuns(ThingType thingType, ThingSubType thingSubType) {
    String str = "";

    if (thingType == ThingType.Еда) {
      str = getBunsFood();
    } else if (thingType == ThingType.Зелье) {
      str = getBunsElixir((ElixirSubType) thingSubType);
    } else if (thingType == ThingType.Свиток) {
      str = getBunsScroll((ScrollSubType) thingSubType);
    } else if (thingType == ThingType.Оружие) {
      str = getBunsWeapon((WeaponSubType) thingSubType);
    }

    game.setTurnDescription(str);
  }

  private static String getBunsFood() {
    String str = "У вас нет еды";
    if (hero.getBackpack().removeItem(ThingType.Еда, OtherSubType.None)) {
      str = TurnDescription.getFoodText(foodHeal(), random);
      hero.incrementFoodEat();
    }

    return str;
  }

  private static String getBunsWeapon(WeaponSubType weapon) {
    String str = "У вас нет " + weapon.toString() + ".";
    if (hero.getBackpack().removeItem(ThingType.Оружие, weapon)) {
      throwWeapon();
      int buns = getWeaponBuns(weapon);
      int oldBuns = hero.gotWeapon() ? hero.getWeaponValue() : 0;

      hero.setPower(hero.getPower() - oldBuns + buns);
      hero.setWeapon(weapon, buns);
      str = "Вы выбросили старое оружие и взяли " + weapon + ". Это оружие дает " + buns + " силы.";
    }

    return str;
  }

  private static void throwWeapon() {
    List<Thing> things = game.getThings();
    ThingSubType subType = hero.getWeaponSubType();

    if (subType != null) {
      Thing weapon = new Thing(ThingType.Оружие, subType);
      weapon.setPosition(newThingPosition());
      things.add(weapon);
    }
  }

  private static Position newThingPosition() {
    char[][] asciiMap = game.getMap().getAsciiMap();
    int x = hero.getPosition().x();
    int y = hero.getPosition().y();

    if (y > 0 && asciiMap[y - 1][x] == '·') {
      y = y - 1;
    } else if (y < 28 && asciiMap[y + 1][x] == '·') {
      y = y + 1;
    }

    if (y == hero.getPosition().y()) {
      if (x > 0 && asciiMap[y][x - 1] == '·') {
        x = x - 1;
      } else if (x < 79 && asciiMap[y][x + 1] == '·') {
        x = x + 1;
      }
    }

    return new Position(x, y);
  }

  private static int getWeaponBuns(WeaponSubType weapon) {
    int floor = game.getHero().getFloor() / 3;
    int buns = 0;
    if (weapon == WeaponSubType.Булава) {
      for (int i = 0; i < 2 + floor; i++)
        buns += random.nextInt(4);
    } else if (weapon == WeaponSubType.ОдноручныйМеч) {
      for (int i = 0; i < 3 + floor; i++)
        buns += random.nextInt(4);
    } else if (weapon == WeaponSubType.Кинжал) {
      for (int i = 0; i < 1 + floor; i++)
        buns += random.nextInt(6);
    } else if (weapon == WeaponSubType.ДвуручныйМеч) {
      for (int i = 0; i < 4 + floor; i++)
        buns += random.nextInt(4);
    } else if (weapon == WeaponSubType.Копье) {
      for (int i = 0; i < 2 + floor; i++)
        buns += random.nextInt(3);
    }
    return buns + 1;
  }

  private static String getBunsElixir(ElixirSubType elixir) {
    boolean[][] fogOfWar = game.getFogOfWar();
    String str = "У вас нет " + elixir.toString() + ".";

    if (hero.getBackpack().removeItem(ThingType.Зелье, elixir)) {
      str = "Вы использовали " + elixir + ".";

      if (elixir == ElixirSubType.Яд) {
        poisonElixir();

      } else if (elixir == ElixirSubType.ЗельеСилы) {
        hero.setPower(hero.getPower() + random.nextInt(3));

      } else if (elixir == ElixirSubType.ЗальеНаживы) {
        for (Thing thing : game.getThings())
          fogOfWar[thing.getPosition().y()][thing.getPosition().x()] = false;

      } else if (elixir == ElixirSubType.ЗельеЛечения) {
        str += healingElixir(2);

      } else if (elixir == ElixirSubType.ЗельеПредчувствия) {
        for (Character monster : game.getMonsters())
          fogOfWar[monster.getPosition().y()][monster.getPosition().x()] = false;

      } else if (elixir == ElixirSubType.БольшоеЗельеЛечения) {
        str += healingElixir(8);
      }

      hero.incrementElixirDrink();
    }

    return str;
  }

  private static void poisonElixir() {
    List<Character> monsters = game.getMonsters();
    List<Character> monstersToRemove = new ArrayList<>();

    for (Character monster : monsters) {
      if (closeToHero(monster.getPosition())) {
        monster.setHealth(monster.getHealth() - (random.nextInt(90) + 10));

        if (monster.getHealth() <= 0) {
          monstersToRemove.add(monster);
        }
      }
    }

    monsters.removeAll(monstersToRemove);
  }

  private static String healingElixir(int count) {
    String text;
    if (hero.getHealth() == hero.getMaxHealth()) {
      int maxHP = (count > 2) ? 4 : 2;
      hero.setMaxHealth(hero.getMaxHealth() + maxHP);
      hero.setHealth(hero.getMaxHealth());
      text = String.format(" Максимальное здоровье увеличено на %d.", maxHP);
    } else {
      text = String.format(" Восстановлено %d здоровья.", heal(count));
    }

    return text;
  }

  private static String getBunsScroll(ScrollSubType scroll) {
    String str = "У вас нет " + scroll.toString() + ".";

    if (hero.getBackpack().removeItem(ThingType.Свиток, scroll)) {

      if (scroll == ScrollSubType.Карта) {
        magicMappingScroll();
      } else if (scroll == ScrollSubType.СвитокСна) {
        sleepScroll();
      } else if (scroll == ScrollSubType.СвитокОпознования) {
        identifyScroll();
      } else if (scroll == ScrollSubType.СвитокТелепортации) {
        teleportScroll();
      } else if (scroll == ScrollSubType.СвитокСозданияМонстра) {
        createMonsterScroll();
      }

      str = "Вы использовали " + scroll + ".";
      hero.incrementScrollRead();
    }

    return str;
  }

  private static void magicMappingScroll() {
    boolean[][] fogOfWar = game.getFogOfWar();

    for (int y = 0; y < 29; y++)
      for (int x = 0; x < Map.MAP_WIDTH; x++)
        fogOfWar[y][x] = false;
  }

  private static void sleepScroll() {
    for (Character monster : game.getMonsters()) {
      if (closeToHero(monster.getPosition()))
        monster.setSleep(random.nextInt(5) + 4);
    }
  }

  private static void identifyScroll() {
    for (Thing thing : game.getThings())
      thing.getName(true);
  }

  private static boolean closeToHero(Position position) {
    boolean res = false;
    int xHero = hero.getPosition().x();
    int yHero = hero.getPosition().y();

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (xHero + i == position.x() && yHero + j == position.y()) {
          res = true;
        }
      }
    }
    return res;
  }

  private static void teleportScroll() {
    char[][] asciiMap = game.getMap().getAsciiMap();
    do {
      hero.getPosition().setPosition(random.nextInt(80), random.nextInt(29));
    } while (asciiMap[hero.getPosition().y()][hero.getPosition().x()] != '·');
    game.revealFogOfWar();
  }

  private static void createMonsterScroll() {
    game.createMonsters(0);
  }

  private static int heal(int count) {
    int heal = 0;

    for (int i = 0; i < count; i++)
      heal += random.nextInt(2 * hero.getLevel() + 1) + 1;
    hero.setHealth(hero.getHealth() + heal);

    return heal;
  }

  private static int foodHeal() {
    int heal = random.nextInt(3 * (hero.getLevel() + 2)) + 1;
    int health = hero.getHealth();
    int maxHealth = hero.getMaxHealth();

    if (health + heal > maxHealth)
      heal = maxHealth - health;
    hero.setHealth(hero.getHealth() + heal);

    return heal;
  }
}