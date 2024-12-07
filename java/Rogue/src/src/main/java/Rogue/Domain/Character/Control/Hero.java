package Rogue.Domain.Character.Control;

import Rogue.Domain.Thing.Things.Backpack;
import Rogue.Domain.Thing.ThingEnums.WeaponSubType;
import Rogue.Domain.Utility.WeaponPair;
import Rogue.Domain.Utility.Position;
import Rogue.Domain.Character.CharacterEnums.*;

public class Hero extends Character {
  private Backpack backpack;
  private int level, exp, levelUpExp, countLoseXP, monsterKills;
  private int gold;
  private WeaponPair weapon;
  private String name;

  public Hero() {
    super(Health.LOW, Power.LOW, Agitility.LOW, Hostility.LOW, Speed.LOW);
    this.position = new Position(40, 12);
    this.backpack = new Backpack();
    this.level = 1;
    this.exp = 0;
    this.levelUpExp = 10;
    this.gold = 0;
    this.monsterName = '@';
    this.weapon = null;
    this.countLoseXP = 0;
    this.monsterKills = 0;
    this.power = 16;
    this.agility = 8;
    this.maxHealth = 20;
    this.health = 20;
    this.name = "Герой";
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
    return weapon == null ? null : weapon.getKey();
  }

  public int getWeaponValue() {
    return weapon == null ? 0 : weapon.getValue();
  }

  public WeaponPair getWeapon() {
    return weapon;
  }

  public void setWeapon(WeaponSubType weapon, int value) {
    this.weapon = new WeaponPair(weapon, value);
  }

  public int getMaxHealth() {
    return maxHealth;
  }

  public void setMaxHealth(int maxHealth) {
    this.maxHealth = maxHealth;
  }

  @Override
  public void setHealth(int health) {
    if (health > maxHealth) {
      this.health = maxHealth;
    } else {
      this.health = health;
    }
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

  public int getCountLoseHP() {
    return countLoseXP;
  }

  public void addCountLoseHP() {
    this.countLoseXP++;
  }

  public void resetCountLoseHP() {
    this.countLoseXP = 0;
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

  public void setName(String name) {
    this.name = name;
  }

  public void setLevel(int level) {
    this.level = level;
  }

  public void setExp(int exp) {
    this.exp = exp;
  }

  public void setGold(int gold) {
    this.gold = gold;
  }
}