package Rogue.Domain.Game.Control;

import java.util.List;
import java.util.Random;

import Rogue.Controllers.ControllerDatalayer;
import Rogue.Domain.Game.Objects.Map;
import Rogue.Domain.Game.Objects.Room;
import Rogue.Domain.Game.Objects.Character.Character;
import Rogue.Domain.Game.Objects.Character.Hero;
import Rogue.Domain.Game.Objects.Thing.Thing;
import Rogue.Domain.Game.Utility.Buns;
import Rogue.Domain.Game.Utility.Direction;
import Rogue.Domain.Game.Utility.Position;
import Rogue.Domain.Game.Utility.TurnDescription;
import Rogue.Domain.Game.Utility.PrePrint.InventoryToPrint;

public class GameData {
  private final Random rand;
  private static GameData instance;

  private final Map map;
  private Hero hero;
  private final CharacterList monsterList;
  private final ThingList thingList;
  private String turnDescription;
  private InventoryToPrint inventoryToPrint;

  private GameData() {
    rand = new Random();
    map = new Map(rand);
    hero = new Hero();
    monsterList = new CharacterList(rand);
    thingList = new ThingList(rand);
    turnDescription = "";
    inventoryToPrint = InventoryToPrint.NONE;

    createNewMap();
  }

  public static GameData getInstance() {
    if (instance == null) {
      instance = new GameData();
    }
    return instance;
  }

  public void loadHero() {
    map.resetFogOfWar();
    Hero temp = ControllerDatalayer.loadGame();
    if (temp != null)
      hero = temp;
    revealFogOfWar();
  }

  public int nextTurn() {
    int damageTaken = 0;

    if (map.getAsciiMap()[hero.getPosition().y()][hero.getPosition().x()] == '·') {
      thingList.getThings(hero);
      damageTaken = monsterList.monstersAction(hero);
    } else {
      monsterList.monstersIdle();
    }

    return damageTaken;
  }

  public void moveHero(Direction dir) {
    boolean heroSleep = false;
    int damageDone = 0;
    int damageTaken = 0;

    if (hero.isSleep()) {
      hero.sleep();
      heroSleep = true;
    } else {
      hero.move(dir);
      if (collision()) {
        damageDone = heroAttack();
        hero.move(Direction.getOpposite(dir));
      }
    }

    if (nextFloor()) {
      hero.setFloor(hero.getFloor() + 1);
      ControllerDatalayer.saveGame();
      createNewMap();
    } else {
      damageTaken = nextTurn();
    }
    revealFogOfWar();

    turnDescription = TurnDescription.getText(hero.getName(), damageDone, damageTaken, heroSleep, rand);
  }

  private int heroAttack() {
    Character target = monsterList.checkMonsters(hero);
    int damageDone = 0;

    if (target != null) {
      damageDone = hero.attack(target);
      if (target.getHealth() <= 0) {
        monsterList.removeMonster(target);
      }
    }

    return damageDone;
  }

  public boolean gameInProgress() {
    return getHero().getHealth() > 0 && getHero().getFloor() <= 21;
  }

  private boolean nextFloor() {
    return map.getAsciiMap()[hero.getPosition().y()][hero.getPosition().x()] == '⇧';
  }

  public void revealFogOfWar() {
    Room room = Room.findRoom(map.getRooms(), hero.getPosition());

    floorResetFogOfWar();
    if (room != null) {
      for (int y = room.y1(); y <= room.y2(); y++) {
        for (int x = room.x1(); x <= room.x2(); x++) {
          map.getFogOfWar()[y][x] = false;
        }
      }
    } else {
      rayCasting();
    }

    int xHero = hero.getPosition().x();
    int yHero = hero.getPosition().y();
    for (int y = yHero - 1; y <= yHero + 1; y++) {
      for (int x = xHero - 1; x <= xHero + 1; x++) {
        map.getFogOfWar()[y][x] = false;
      }
    }
  }

  private void floorResetFogOfWar() {
    for (int y = 0; y < Map.MAP_HEIGHT; y++) {
      for (int x = 0; x < Map.MAP_WIDTH; x++) {
        if (!map.getFogOfWar()[y][x]) {
          char c = map.getAsciiMap()[y][x];
          if (c == '·' || c == '⇧') {
            map.getFogOfWar()[y][x] = true;
          }
        }
      }
    }
  }

  private void rayCasting() {
    char[][] asciiMap = map.getAsciiMap();
    boolean[][] fog = map.getFogOfWar();
    int xHero = hero.getPosition().x();
    int yHero = hero.getPosition().y();

    int[][] directions = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
    for (int[] dir : directions) {
      int dx = dir[0];
      int dy = dir[1];
      int delta = 1;
      char c = asciiMap[yHero + dy * delta][xHero + dx * delta];

      while (c == '#' || c == '+') {
        if (c == '+' && delta < 5) {
          processRoomVisibility(xHero, yHero, dx, dy, delta);
        }
        fog[yHero + dy * delta][xHero + dx * delta] = false;
        c = asciiMap[yHero + dy * ++delta][xHero + dx * delta];
      }
    }
  }

  private void processRoomVisibility(int xHero, int yHero, int dx, int dy, int delta) {
    char[][] asciiMap = map.getAsciiMap();
    boolean[][] fog = map.getFogOfWar();
    Room[] rooms = map.getRooms();
    Room room = Room.findRoom(rooms, new Position(xHero + dx * delta, yHero + dy * delta));
    for (int i = 1;; i++) {
      for (int range = -(i / delta); range <= (i / delta); range++) {
        int y = yHero + dy * (delta + i) + dx * range / 3;
        int x = xHero + dx * (delta + i) + dy * range;
        if (Room.findRoom(rooms, new Position(x, y)) == room) {
          fog[y][x] = false;
        }
      }

      char c = asciiMap[yHero + dy * (delta + i)][xHero + dx * (delta + i)];
      if (c != '·' && c != '⇧') {
        break;
      }
    }
  }

  private boolean collision() {
    char c = map.getAsciiMap()[hero.getPosition().y()][hero.getPosition().x()];

    return (c == '|') || (c == '—') || (c == ' ') || monsterCollision();
  }

  private boolean monsterCollision() {
    return monsterList.checkMonsters(hero) != null;
  }

  private void createNewMap() {
    map.generateMap(hero);
    monsterList.clearMonsterList();
    monsterList.createMonsters(map.getTempMap(), map.getRooms(), hero.getFloor(), checkHard());
    thingList.clearThingList();
    thingList.createThing(map.getTempMap(), hero.getFloor(), checkHard());
    hero.resetLostHP();
    hero.resetMonsterKills();
    revealFogOfWar();
  }

  private int checkHard() {
    int lostHP = hero.getLostHP();
    int kills = hero.getMonsterKills();

    int difficulty = 0;

    if (kills > 0) {
      if (lostHP / kills >= 6) {
        difficulty = -1;
      } else if (lostHP / kills <= 2) {
        difficulty = 1;
      }
    }

    return difficulty;
  }

  public Hero getHero() {
    return hero;
  }

  public void createMonsters(int checkHard) {
    monsterList.createMonsters(map.getAsciiMap(), map.getRooms(), hero.getFloor(), checkHard);
  }

  public List<Character> getMonsters() {
    return monsterList.getMonsters();
  }

  public List<Thing> getThings() {
    return thingList.getThingsList();
  }

  public char[][] getAsciiMap() {
    return map.getAsciiMap();
  }

  public char[][] getTempMap() {
    return map.getTempMap();
  }

  public boolean[][] getFogOfWar() {
    return map.getFogOfWar();
  }

  public Room[] getRooms() {
    return map.getRooms();
  }

  public Map getMap() {
    return map;
  }

  public void setTurnDescription(String s) {
    turnDescription = s;
  }

  public String getTurnDescription() {
    return turnDescription;
  }

  public void inventoryToPrint(char c) {
    inventoryToPrint = InventoryToPrint.get(c);
  }

  public InventoryToPrint getInventoryToPrint() {
    return inventoryToPrint;
  }

  public void moveHero(char c) {
    Direction dir = Direction.get(c);

    if (dir != null) {
      moveHero(dir);
      hero.incrementSteps();
    }
  }

  public void backpack(char c, char lastC) {
    if (c >= '1' && c <= '9') {
      Buns.useThing(c, lastC);
    }
    inventoryToPrint(c);
  }
}