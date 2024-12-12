package Rogue.Domain.Game.Objects.Character;

import Rogue.Domain.Game.Objects.Room;
import Rogue.Domain.Game.Objects.Character.CharacterEnums.*;
import Rogue.Domain.Game.Utility.*;

import java.util.Random;

public class Character {
  protected int health, maxHealth, power, agility, hostility, speed;
  protected int baseHostility;
  protected int sleep;
  protected Random rand;
  protected Position position;
  protected char monsterName;
  protected Room room;

  protected Character(Health health, Power power, Agility agility,
      Hostility hostility, Speed speed) {

    this.health = health.getValue();
    this.maxHealth = this.health;
    this.power = power.getValue();
    this.agility = agility.getValue();
    this.hostility = hostility.getValue();
    this.speed = speed.getValue();
    this.baseHostility = this.hostility;
    this.sleep = 0;
    this.rand = new Random();
    this.position = new Position(0, 0);
    this.room = null;
  }

  public int attack(Character target) {
    return Battle.attack(this, target, rand);
  }

  public boolean move(Direction direction) {
    boolean moved = true;
    hostility = 4;

    if (direction == Direction.UP)
      move(0, -1);
    else if (direction == Direction.DOWN)
      move(0, 1);
    else if (direction == Direction.LEFT)
      move(-1, 0);
    else if (direction == Direction.RIGHT)
      move(1, 0);
    else {
      moved = false;
    }

    return moved;
  }

  protected void move(int x, int y) {
    position.setPosition(position.x() + x, position.y() + y);
  }

  public void sleep() {
    if (sleep != 0)
      sleep--;
  }

  public void idle() {
    hostility = baseHostility;
  }

  public char getMonsterName() {
    return monsterName;
  }

  public int getMonsterExp() {
    return ((maxHealth / 50 + 1) * power * (agility / 10 + 1)) / 3 + 2;
  }

  public int getMonsterGold() {
    return getMonsterExp() * 10 + rand.nextInt(10);
  }

  public boolean isSleep() {
    return sleep != 0;
  }

  public void setSleep(int time) {
    this.sleep = time;
  }

  public int getHealth() {
    return health;
  }

  public void setHealth(int health) {
    this.health = health;
  }

  public int getPower() {
    return power;
  }

  public void setPower(int power) {
    this.power = power;
  }

  public int getAgility() {
    return agility;
  }

  public Position getPosition() {
    return position;
  }

  public void setPosition(int x, int y) {
    position.setPosition(x, y);
  }

  public void setPosition(Position pos) {
    setPosition(pos.x(), pos.y());
  }

  public void setRoom(Room room) {
    this.room = room;
  }

  public void addFloorDifficulty(int floor) {
    health = countFloorDifficulty(health, floor, 0.07f);
    power = countFloorDifficulty(power, floor, 0.06f);
    agility = countFloorDifficulty(agility, floor, 0.04f);
  }

  private int countFloorDifficulty(int num, int floor, float coef) {
    return Math.round(num * (1 + floor * coef));
  }

  public void setAgility(int agility) {
    this.agility = agility;
  }

  public int getHostility() {
    return hostility;
  }

  public void upStats() {
    float coef = 1.25f;
    health = changeStats(health, coef);
    power = changeStats(power, coef);
    agility = changeStats(agility, coef);
  }

  public void downStats() {
    float coef = 0.75f;
    health = changeStats(health, coef);
    power = changeStats(power, coef);
    agility = changeStats(agility, coef);
  }

  private int changeStats(int stat, float percent) {
    return Math.round(stat * percent);
  }
}