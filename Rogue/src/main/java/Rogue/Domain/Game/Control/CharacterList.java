package Rogue.Domain.Game.Control;

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.util.Random;

import Rogue.Domain.Game.Objects.Map;
import Rogue.Domain.Game.Objects.Room;
import Rogue.Domain.Game.Objects.Character.Character;
import Rogue.Domain.Game.Objects.Character.MonsterFabric;
import Rogue.Domain.Game.Objects.Character.Monsters.Ogre;
import Rogue.Domain.Game.Utility.*;

public class CharacterList {
  private final ArrayList<Character> monsters;
  private final Random rand;

  public CharacterList(Random rand) {
    this.rand = rand;
    monsters = new ArrayList<>();
  }

  public void createMonsters(char[][] map, Room[] rooms, int floor, int checkHard) {
    int count = 5 + floor / 2 + checkHard * 2;

    for (int i = 0; i < count; i++) {
      Position emptySpace = getEmptySpace(map);
      Room room = Room.findRoom(rooms, emptySpace);
      monsters.add(MonsterFabric.createMonster(emptySpace, room, floor));

      if (floor > 3 && checkHard == 1) {
        monsters.get(i).upStats();
      } else if (floor > 3 && checkHard == -1) {
        monsters.get(i).downStats();
      }
    }
  }

  private Position getEmptySpace(char[][] map) {
    int x, y;
    do {
      x = rand.nextInt(Map.MAP_WIDTH);
      y = rand.nextInt(Map.MAP_HEIGHT);
    } while (map[y][x] != '·');
    map[y][x] = 'M';

    return new Position(x, y);
  }

  public void clearMonsterList() {
    monsters.clear();
  }

  public void removeMonster(Character monster) {
    monsters.remove(monster);
  }

  public int monstersAction(Character hero) {
    int damageDone = 0;

    List<Character> angryMonsters = getMonsters(hero.getPosition());
    for (Character monster : angryMonsters) {
      if (monster.isSleep()) {
        monster.sleep();
        continue;
      }

      Direction dir = getHeroDirection(monster.getPosition(), hero.getPosition());
      if (!monster.move(dir)) {
        damageDone = monster.attack(hero);
      } else if (monster instanceof Ogre) {
        dir = getHeroDirection(monster.getPosition(), hero.getPosition());
        monster.move(dir);
      }
    }

    return damageDone;
  }

  public void monstersIdle() {
    for (Character monster : monsters) {
      if (monster.isSleep()) {
        monster.sleep();
      } else {
        monster.idle();
      }
    }
  }

  private Direction getHeroDirection(Position monsterPos, Position heroPos) {
    Direction dir = null;
    int deltaX = heroPos.x() - monsterPos.x();
    int deltaY = heroPos.y() - monsterPos.y();

    if (Math.abs(deltaY) > 1 || Math.abs(deltaX) > 1) {
      if (Math.abs(deltaX) > Math.abs(deltaY)) {
        dir = (deltaX > 0) ? Direction.RIGHT : Direction.LEFT;
      } else {
        dir = (deltaY > 0) ? Direction.DOWN : Direction.UP;
      }
    }

    return dir;
  }

  public List<Character> getMonsters() {
    return monsters;
  }

  public List<Character> getMonsters(Position heroPos) {
    List<Character> result = Collections.synchronizedList(new ArrayList<>());

    for (Character monster : monsters) {
      if (monsterSeeHero(heroPos, monster)) {
        result.add(monster);
      } else {
        monster.idle();
      }
    }

    return result;
  }

  private boolean monsterSeeHero(Position heroPos, Character monster) {
    int radius = monster.getHostility();
    int monsterX = monster.getPosition().x();
    int monsterY = monster.getPosition().y();
    int minX = monsterX - radius;
    int maxX = monsterX + radius;
    int minY = monsterY - radius;
    int maxY = monsterY + radius;

    return heroPos.x() >= minX && heroPos.x() <= maxX && heroPos.y() >= minY && heroPos.y() <= maxY;
  }

  public Character checkMonsters(Character player) {
    Character res = null;
    int x = player.getPosition().x();
    int y = player.getPosition().y();

    for (Character monster : monsters) {
      if (monster.getPosition().x() == x && monster.getPosition().y() == y) {
        res = monster;
        break;
      }
    }

    return res;
  }
}