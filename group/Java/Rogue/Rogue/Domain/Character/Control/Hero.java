package Domain.Character.Control;

import Domain.Thing.Things.Backpack;
import Domain.Thing.ThingEnums.WeaponSubType;
import Domain.Utility.WeaponPair;
import Domain.Utility.Position;
import Domain.Character.CharacterEnums.*;

public class Hero extends Character {
  private Backpack backpack;
  private int level, exp, levelUpExp, maxHealth, countLoseXP, monsterKills;
  private int gold;
  private WeaponPair weapon;
  private String name;

  public Hero() {
    super(Health.LOW, Power.LOW, Agitility.LOW, Hostility.LOW, Speed.LOW);
    this.position = new Position(40, 12);
    this.backpack = new Backpack();
    this.maxHealth = Health.LOW.getValue();
    this.level = 1;
    this.exp = 0;
    this.levelUpExp = 10;
    this.gold = 0;
    this.monsterName = '@';
    this.weapon = null;
    this.countLoseXP = 0;
    this.monsterKills = 0;
    this.setPower(16);
    this.setAgility(8);
    this.setMaxHealth(20);
    this.setHealth(20);
    this.name = "Герой";
  }

  public void addLevel() {
    level++;
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

  @Override
  public int getMonsterExp() {
    return 0;
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
    if (health > maxHealth) {
      health = maxHealth;
    }
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

  public void setLevel(int level) {
    this.level = level;
  }

  public int getExp() {
    return exp;
  }

  public void setExp(int exp) {
    this.exp = exp;
  }

  public int getGold() {
    return gold;
  }

  public void addGold(int gold) {
    this.gold += gold;
  }

  public int getLevelUpExp() {
    return levelUpExp;
  }

  public void setLevelUpExp(int levelUpExp) {
    this.levelUpExp = levelUpExp;
  }

  public void setBackpack(Backpack backpack) {
    this.backpack = backpack;
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
}