package Rogue.Domain.Game.Utility;

import java.util.Random;

import Rogue.Domain.Game.Objects.Character.Character;
import Rogue.Domain.Game.Objects.Character.Hero;
import Rogue.Domain.Game.Objects.Character.Monsters.SnakeMage;
import Rogue.Domain.Game.Objects.Character.Monsters.Vampire;

public class Battle {
  private Battle() {
  }

  public static int attack(Character attacker, Character defender, Random rand) {
    int damage = -1;

    if (attackHit(attacker, defender, rand)) {
      damage = attacker.getPower();
      defender.setHealth(defender.getHealth() - damage);

      if (attacker instanceof Hero hero) {
        hero.incrementHitOk();
      }

      if (defender instanceof Hero hero) {
        hero.incrementHitMiss();
        hero.addLostHP(damage);
        if (attacker instanceof Vampire vampire) {
          hero.setMaxHealth(hero.getMaxHealth() - rand.nextInt(vampire.getPower()));
        } else if (attacker instanceof SnakeMage && rand.nextBoolean()) {
          hero.setSleep(1);
        }

      } else if (defender.getHealth() <= 0 && attacker instanceof Hero hero) {
        hero.addGold(defender.getMonsterGold());
        hero.addExp(defender.getMonsterExp());
        hero.addMonsterKills();
        hero.incrementMonstersKill();
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
    boolean freeHit = false;

    if (attacker instanceof Vampire vampire && vampire.isFirstAttack()) {
      freeHit = true;
      vampire.setFirstAttack(false);
    }

    return freeHit;
  }
}