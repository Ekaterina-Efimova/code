package Rogue.Domain.Thing.Things;

import java.util.Random;

import Rogue.Domain.Character.Control.*;
import Rogue.Domain.Character.Control.Character;
import Rogue.Domain.Game.Objects.MapControl;
import Rogue.Domain.Game.Objects.Room;
import Rogue.Domain.Thing.ThingEnums.*;
import Rogue.Domain.Utility.Position;
import Rogue.Domain.Utility.TurnDescription;
import Rogue.Domain.Thing.Control.ThingList;

public class Buns {
  private Random random;
  private MapControl mapControl;
  private Hero hero;

  public Buns() {
    this.random = new Random();
  }

  public void setMapControl(MapControl mapControl) {
    this.mapControl = mapControl;
    this.hero = mapControl.getPlayer();
  }

  public String chooseBunsType(ThingType thingType, ThingSubType thingSubType) {
    String str = "У вас нет этой вещи.";

    if (thingType == ThingType.Еда) {
      str = getBunsFood();
    } else {
      if (thingType == ThingType.Зелье) {
        str = getBuns((ElixirSubType) thingSubType, mapControl.getFogOfWar(), mapControl.getThingList(),
            mapControl.getMonsterList());
      } else if (thingType == ThingType.Свиток) {
        str = getBuns((ScrollSubType) thingSubType, mapControl.getAsciiMap(), mapControl.getFogOfWar(),
            mapControl.getRooms(), mapControl.getThingList(), mapControl.getMonsterList());
      } else if (thingType == ThingType.Оружие) {
        str = getBuns((WeaponSubType) thingSubType, mapControl.getAsciiMap(), mapControl.getThingList());
      }
    }

    return str;
  }

  private String getBunsFood() {
    String str = "У вас нет еды";
    if (hero.getBackpack().removeItem(ThingType.Еда, OtherSubType.None)) {
      str = TurnDescription.getFoodText(foodHeal(), random);
    }

    return str;
  }

  private String getBuns(WeaponSubType weapon, char[][] asciiMap, ThingList thingList) {
    String str = "У вас нет " + weapon.toString() + ".";
    if (hero.getBackpack().removeItem(ThingType.Оружие, weapon)) {
      throwWeapon(asciiMap, thingList);
      int buns = getWeaponBuns(weapon);

      int oldBuns = 0;
      if (hero.getWeapon() != null)
        oldBuns = hero.getWeaponValue();

      hero.setPower(hero.getPower() - oldBuns + buns);
      hero.setWeapon(weapon, buns);
      str = "Вы выбросили старое оружие и взяли " + weapon.toString() + ". Это оружие дает " + buns
          + " силы.";
    }

    return str;
  }

  private void throwWeapon(char[][] asciiMap, ThingList thingList) {
    ThingSubType subType = hero.getWeaponSubType();

    if (subType != null) {
      Thing weapon = new Thing(ThingType.Оружие, subType);
      weapon.setPosition(newThingPosition(asciiMap));
      thingList.addThing(weapon);
    }
  }

  private Position newThingPosition(char[][] asciiMap) {
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

  private int getWeaponBuns(WeaponSubType weapon) {
    int floor = mapControl.getFloor() / 3;
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

  private String getBuns(ElixirSubType elixir, boolean[][] fogOfWar, ThingList thingList, CharacterList monsterList) {
    String str = "У вас нет " + elixir.toString() + ".";

    if (hero.getBackpack().removeItem(ThingType.Зелье, elixir)) {
      str = "Вы использовали " + elixir.toString() + ".";

      if (elixir == ElixirSubType.Яд) {
        poisonElixir(monsterList);
      } else if (elixir == ElixirSubType.ЗельеСилы) {
        hero.setPower(hero.getPower() + random.nextInt(3));
      } else if (elixir == ElixirSubType.ЗальеНаживы) {
        for (Thing thing : thingList.getThingsList())
          fogOfWar[thing.getPosition().y()][thing.getPosition().x()] = false;
      } else if (elixir == ElixirSubType.ЗельеЛечения) {
        str += healingElixir(2);
      } else if (elixir == ElixirSubType.ЗельеПредчувствия) {
        for (Character monster : monsterList.getMonsters())
          fogOfWar[monster.getPosition().y()][monster.getPosition().x()] = false;
      } else if (elixir == ElixirSubType.БольшоеЗельеЛечения) {
        str += healingElixir(8);
      }

    }

    return str;
  }

  private void poisonElixir(CharacterList monsterList) {
    for (Character monster : monsterList.getMonsters()) {
      if (closeToHero(monster.getPosition())) {
        monster.setHealth(monster.getHealth() - random.nextInt(100) + 10);
        if (monster.getHealth() <= 0) {
          monsterList.removeMonster(monster);
        }
      }
    }
  }

  private String healingElixir(int count) {
    String text = "";
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

  private String getBuns(ScrollSubType scroll, char[][] map, boolean[][] fogOfWar, Room[] rooms, ThingList thingList,
      CharacterList monsterList) {
    String str = "У вас нет " + scroll.toString() + ".";

    if (hero.getBackpack().removeItem(ThingType.Свиток, scroll)) {

      if (scroll == ScrollSubType.Карта) {
        magicMappingScroll(fogOfWar);
      } else if (scroll == ScrollSubType.СвитокСна) {
        sleepScroll(monsterList);
      } else if (scroll == ScrollSubType.СвитокОпознования) {
        indentifyScroll(thingList);
      } else if (scroll == ScrollSubType.СвитокТелепортации) {
        teleportScroll(map);
      } else if (scroll == ScrollSubType.СвитокСозданияМонстра) {
        createMonsterScroll(monsterList, map, rooms);
      } else if (scroll == ScrollSubType.СвитокСвета) {
        lightScroll(fogOfWar, rooms);
      }

      str = "Вы использовали " + scroll.toString() + ".";
    }

    return str;
  }

  private void magicMappingScroll(boolean[][] fogOfWar) {
    for (int y = 0; y < 29; y++)
      for (int x = 0; x < 80; x++)
        fogOfWar[y][x] = false;
  }

  private void sleepScroll(CharacterList monsterList) {
    for (Character monster : monsterList.getMonsters()) {
      if (closeToHero(monster.getPosition()))
        monster.setSleep(random.nextInt(5) + 4);
    }
  }

  private void indentifyScroll(ThingList thingList) {
    for (Thing thing : thingList.getThingsList())
      thing.getName(true);
  }

  private boolean closeToHero(Position position) {
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

  private void teleportScroll(char[][] asciiMap) {
    do {
      hero.getPosition().setPosition(random.nextInt(80), random.nextInt(29));
    } while (asciiMap[hero.getPosition().y()][hero.getPosition().x()] != '·');
  }

  private void createMonsterScroll(CharacterList monsterList, char[][] map, Room[] rooms) {
    monsterList.createMonsters(map, rooms, hero.getLevel(), 0);
  }

  private void lightScroll(boolean[][] fogOfWar, Room[] rooms) {
    Room room = Room.findRoom(rooms, hero.getPosition());
    for (int y = room.y1(); y <= room.y2(); y++) {
      for (int x = room.x1(); x <= room.x2(); x++) {
        fogOfWar[y][x] = false;
      }
    }
  }

  private int heal(int count) {
    int heal = 0;

    for (int i = 0; i < count; i++)
      heal += random.nextInt(2 * hero.getLevel() + 1) + 1;
    hero.setHealth(hero.getHealth() + heal);

    return heal;
  }

  private int foodHeal() {
    int heal = random.nextInt(3 * (hero.getLevel() + 2)) + 1;
    int health = hero.getHealth();
    int maxHealth = hero.getMaxHealth();

    if (health + heal > maxHealth)
      heal = maxHealth - health;
    hero.setHealth(hero.getHealth() + heal);

    return heal;
  }
}