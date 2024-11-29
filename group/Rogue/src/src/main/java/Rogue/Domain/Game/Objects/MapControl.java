package Rogue.Domain.Game.Objects;

import java.util.Random;

import Rogue.Domain.Character.Control.*;
import Rogue.Domain.Character.Control.Character;
import Rogue.Domain.Thing.Control.ThingList;
import Rogue.Domain.Thing.ThingEnums.ThingSubType;
import Rogue.Domain.Thing.ThingEnums.ThingType;
import Rogue.Domain.Thing.Things.Buns;
import Rogue.Domain.Utility.Direction;
import Rogue.Domain.Utility.TurnDescription;

public class MapControl {
  private Random rand;
  private Map map;
  private Hero player;
  private CharacterList monsterList;
  private ThingList thingList;
  private boolean newFloor;

  public MapControl(Hero hero) {
    rand = new Random();
    map = new Map(rand);
    player = hero;
    monsterList = new CharacterList(rand);
    thingList = new ThingList(rand);
    newFloor = false;

    createNewMap();
  }

  public int nextTurn() {
    int damageTaken = 0;

    if (map.getAsciiMap()[player.getPosition().y()][player.getPosition().x()] == '·') {
      thingList.getThings(player);
      damageTaken = monsterList.monstersAction(player);
    } else {
      monsterList.monstersIdle();
    }

    return damageTaken;
  }

  public void movePlayer(Direction dir, char[][] printChar) {
    boolean heroSleep = false;
    int damageDone = 0;
    int damageTaken = 0;

    if (player.isSleep()) {
      player.sleep();
      heroSleep = true;
    } else {
      player.move(dir);
      if (collision()) {
        damageDone = heroAttack();
        player.move(Direction.getOpposite(dir));
      }
    }

    if (nextFloor()) {
      newFloor = true;
      createNewMap();
    } else {
      newFloor = false;
      damageTaken = nextTurn();
    }
    revealFogOfWar();

    printChar[0] = TurnDescription.getText(player.getName(), damageDone, damageTaken, heroSleep, rand).toCharArray();
  }

  private int heroAttack() {
    Character target = monsterList.checkMonsters(player);
    int damageDone = 0;

    if (target != null) {
      damageDone = player.attack(target);
      if (target.getHealth() <= 0) {
        monsterList.removeMonster(target);
      }
    }

    return damageDone;
  }

  private boolean nextFloor() {
    return map.getAsciiMap()[player.getPosition().y()][player.getPosition().x()] == '⇧';
  }

  private void revealFogOfWar() {
    int xPlayer = player.getPosition().x();
    int yPlayer = player.getPosition().y();

    for (int y = yPlayer - 1; y <= yPlayer + 1; y++) {
      for (int x = xPlayer - 1; x <= xPlayer + 1; x++) {
        map.getFogOfWar()[y][x] = false;
      }
    }
  }

  public String chooseBunsType(char c, char lastC) {
    Buns buns = new Buns();
    buns.setMapControl(this);

    ThingType thingType = ThingType.parseThingType(lastC);
    ThingSubType thingSubType = ThingSubType.parseThingSubType(thingType, c);

    String action = "";
    if(thingType != null && thingSubType != null) 
      action = buns.chooseBunsType(thingType, thingSubType);

    return action;
  }

  private boolean collision() {
    char c = map.getAsciiMap()[player.getPosition().y()][player.getPosition().x()];

    return (c == '|') || (c == '—') || (c == ' ') || monsterCollision();
  }

  private boolean monsterCollision() {
    return monsterList.checkMonsters(player) != null;
  }

  private void createNewMap() {
    map.generateMap(player);
    monsterList.clearMonsterList();
    monsterList.createMonsters(map.getTempMap(), map.getRooms(), map.getFloor(), checkHard());
    thingList.clearThingList();
    thingList.createThing(map.getTempMap(), map.getFloor(), checkHard());
    player.resetCountLoseHP();
    player.resetMonsterKills();
    revealFogOfWar();
  }

  private int checkHard() {
    int attacked = player.getCountLoseHP();
    int kills = player.getMonsterKills();

    int difficulty = 0;

    if (kills > 0) {
      if (attacked / kills >= 5) {
        difficulty = -1;
      } else if (attacked / kills <= 1) {
        difficulty = 1;
      }
    }

    return difficulty;
  }

  public boolean isNewFloor() {
    return newFloor;
  }

  public Hero getPlayer() {
    return player;
  }

  public CharacterList getMonsterList() {
    return monsterList;
  }

  public ThingList getThingList() {
    return thingList;
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

  public int getFloor() {
    return map.getFloor();
  }

  public Room[] getRooms() {
    return map.getRooms();
  }

  public void setPlayer(Hero player) {
    this.player = player;
  }

  public void setFloor(int floor) {
    map.setFloor(floor);
  }
}