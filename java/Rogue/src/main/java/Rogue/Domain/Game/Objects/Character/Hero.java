package Rogue.Domain.Game.Objects.Character;

import Rogue.Domain.Game.Objects.Backpack;
import Rogue.Domain.Game.Objects.Character.CharacterEnums.*;
import Rogue.Domain.Game.Objects.Thing.ThingEnums.WeaponSubType;
import Rogue.Domain.Game.Utility.Position;

public class Hero extends Character {
  public record Weapon(WeaponSubType type, Integer strength) {
  }

  private final Backpack backpack;
  private int level, exp, levelUpExp, lostHP, monsterKills;
  private int gold, floor;
  private int monstersKill, foodEat, elixirDrink, scrollRead, hitOk, hitMiss, steps;
  private Weapon weapon;
  private String name;

  public Hero() {
    super(Health.LOW, Power.LOW, Agility.LOW, Hostility.LOW, Speed.LOW);
    this.position = new Position(40, 12);
    this.backpack = new Backpack();
    this.level = 1;
    this.exp = 0;
    this.levelUpExp = 10;
    this.gold = 0;
    this.monsterName = '@';
    this.weapon = null;
    this.lostHP = 0;
    this.monsterKills = 0;
    this.power = 16;
    this.agility = 8;
    this.maxHealth = 20;
    this.health = 20;
    this.name = "Герой";
    this.floor = 1;
    this.monstersKill = 0;
    this.foodEat = 0;
    this.elixirDrink = 0;
    this.scrollRead = 0;
    this.hitOk = 0;
    this.hitMiss = 0;
    this.steps = 0;
  }

  public void addExp(int exp) {
    this.exp += exp;
    if (this.exp >= levelUpExp) {
      levelUp();
    }
  }

  private void levelUp() {
    maxHealth += 10;
    setHealth(maxHealth);
    setPower(getPower() + 5);
    setAgility(getAgility() + 1);
    level++;
    exp -= levelUpExp;
    levelUpExp = levelUpExp * 2;
  }

  public WeaponSubType getWeaponSubType() {
    return weapon == null ? null : weapon.type();
  }

  public int getWeaponValue() {
    return weapon == null ? 0 : weapon.strength();
  }

  public boolean gotWeapon() {
    return weapon != null;
  }

  public void setWeapon(WeaponSubType type, int strength) {
    this.weapon = new Weapon(type, strength);
  }

  public int getMaxHealth() {
    return maxHealth;
  }

  public void setMaxHealth(int maxHealth) {
    this.maxHealth = maxHealth;
  }

  @Override
  public void setHealth(int health) {
    this.health = Math.min(health, maxHealth);
  }

  public Backpack getBackpack() {
    return backpack;
  }

  public int getLevel() {
    return level;
  }

  public int getExp() {
    return exp;
  }

  public int getGold() {
    return gold;
  }

  public void addGold(int gold) {
    this.gold += gold;
  }

  public int getLostHP() {
    return lostHP;
  }

  public void addLostHP(int loseHP) {
    this.lostHP += loseHP;
  }

  public void resetLostHP() {
    this.lostHP = 0;
  }

  public int getMonsterKills() {
    return monsterKills;
  }

  public void addMonsterKills() {
    this.monsterKills++;
  }

  public void resetMonsterKills() {
    this.monsterKills = 0;
  }

  public String getName() {
    return name;
  }

  public int getFloor() {
    return floor;
  }

  public void setFloor(int floor) {
    this.floor = floor;
  }

  public void setName(String name) {
    this.name = name;
  }

  public int getKills() {
    return monstersKill;
  }

  public void incrementMonstersKill() {
    this.monstersKill++;
  }

  public int getFoodEat() {
    return foodEat;
  }

  public void incrementFoodEat() {
    this.foodEat++;
  }

  public int getElixirDrink() {
    return elixirDrink;
  }

  public void incrementElixirDrink() {
    this.elixirDrink++;
  }

  public int getScrollRead() {
    return scrollRead;
  }

  public void incrementScrollRead() {
    this.scrollRead++;
  }

  public int getHitOk() {
    return hitOk;
  }

  public void incrementHitOk() {
    this.hitOk++;
  }

  public int getHitMiss() {
    return hitMiss;
  }

  public void incrementHitMiss() {
    this.hitMiss++;
  }

  public int getSteps() {
    return steps;
  }

  public void incrementSteps() {
    this.steps++;
  }
}