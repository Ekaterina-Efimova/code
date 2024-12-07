package Rogue.Domain.Utility;

import Rogue.Domain.Character.Control.Character;
import Rogue.Domain.Character.Control.Hero;
import Rogue.Domain.Character.Monsters.SnakeMage;
import Rogue.Domain.Character.Monsters.Vampire;

import java.util.Random;

public class Battle {
  private Battle() {
  }

  public static int attack(Character attacker, Character defender, Random rand) {
    int damage = -1;

    if (attackHit(attacker, defender, rand)) {
      damage = attacker.getPower();
      defender.setHealth(defender.getHealth() - damage);

      if (defender instanceof Hero) {
        Hero hero = (Hero) defender;

        hero.addCountLoseHP();
        if (attacker instanceof Vampire) {
          hero.setMaxHealth(hero.getMaxHealth() - rand.nextInt(attacker.getPower()));
        } else if (attacker instanceof SnakeMage && rand.nextBoolean()) {
          hero.setSleep(1);
        }

      } else if (defender.getHealth() <= 0) {
        ((Hero) attacker).addGold(defender.getMonsterGold());
        ((Hero) attacker).addExp(defender.getMonsterExp());
        ((Hero) attacker).addMonsterKills();
      }
    }

    return damage;
  }

  private static boolean attackHit(Character attacker, Character defender, Random rand) {
    boolean vampireFirstAttack = vampireFirstAttack(attacker);

    int agilityDiff = defender.getAgility() - attacker.getAgility();
    int hitTarget = 50 * (1 + agilityDiff / (20 + agilityDiff));
    boolean hit = (rand.nextInt(100) >= hitTarget);

    return vampireFirstAttack || hit;
  }

  private static boolean vampireFirstAttack(Character attacker) {
    boolean vampireFirstAttack = false;

    if (attacker instanceof Vampire && ((Vampire) attacker).isFirstAttack()) {
      vampireFirstAttack = true;
      ((Vampire) attacker).setFirstAttack(false);
    }

    return vampireFirstAttack;
  }
}