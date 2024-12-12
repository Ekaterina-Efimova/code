package Rogue.Domain.Game.Utility;

import java.util.Random;

public class TurnDescription {
  private TurnDescription() {
  }

  private static final String[] heroSleepAlone = {
      "%s проспал весь ход.",
      "%s пробежал целый километр! К сожалению только во сне.",
      "%s считает овец.",
      "ZZZZ... *звуки храпа*",
      "Внутренний голос приказал отдыхать. Приказы, как известно, не обсуждаются.",
  };

  private static final String[] heroSleepAndDodge = {
      "%s внезапно заснул и упал, монстр промахнулся.",
      "%s так сладко спит, что монстр не решился его будить.",
      "Монстр замахнулся и ударил, но %s перевернулся на другой бок.",
  };

  private static final String[] heroSleepAndGetHit = {
      "Во сне %s болно били и нанесли %d урона.",
      "%s попросил ущипнуть себя, чтобы проверить, спит ли он. %d урона.",
      "%s хотел спать и сказал что ему сегодня ко второй. Монстр не прогуливает и нанес %d урона.",
      "Посреди боя %s заснул, но монстр решил помочь привести его в чувство, ударив на %d урона.",
      "\"Еще 5 минуточек...\" - бормочет %s, получая %d урона.",
      "Так хорошо притворился спящим, чтобы ошеломить врага внезапной атакой, что случайно заснул - %2$d хп.",
  };

  private static final String[] heroRunAndDodge = {
      "%s забыл в каком направлении монстр и отошел в сторону от удара.",
      "Монстр ударил со всей силы, но %s уже ушел.",
      "Пока монстр обдумывал стратегию на бой %s убежал."
  };

  private static final String[] heroRunAndGetHit = {
      "%s гордо бежит по направлению от монстра. Монстр трусливо бьет в спину на %d урона.",
      "При попытке сбажать %s больно бьется мизинчиком на %d урона.",
      "Во время побега %s наступает на банановую кожуру. %d урона от падения.",
  };

  private static final String[] heroMissAlone = {
      "В сумашедшем боевом танце %s с монстром выдыхаются из сил и забывают атаковать",
      "%s и монстр устроили танцевальный баттл вместо битвы.",
      "Противники так напряженно следили за каждым движением друг друга, что ход закончился.",
      "Увидев, насколько безжалостно %s убивает время, монстр спрятался в кусты.",
      "\"Ну я же точно попал!\" - уверяет %s, разрубив воздух.",
  };

  private static final String[] heroMissAndGetHit = {
      "%s поскользнулся и упал лицом на противника нанеся себе %d урона.",
      "Эпичный замах %s заканчивается эпичным промахом и получением %d урона.",
      "%s атакует монстра, но попадает по себе на %d урона.",
      "Пока %s думал что ему делать, его ударили и нанесли %d урона.",
      "%s забыл сколько у него здоровья и спросил у монстра, тот назвал число на %d меньше.",
      "Монстр отколупывает от %s кусочек полоски здоровья размером в %d хп.",
      "Монстр роняет тяжелый взгляд на ногу %s, нанося %d урона.",
  };

  private static final String[] heroHitAlone = {
      "%s ударил на %d урона. Противник забыл атаковать.",
      "%s наносит удар на %d урона. Монстр в шоке!",
      "%s провел свою коронную атаку, спросив у монстра, что у него за спиной и нанес %d урона.",
      "%s обзывает противника и нанесит ему психологическую травму на %d урона.",
      "%s ставит подножку монстру на %d урона. Монстр заплакал и побежал жаловаться.",
      "Вооружившись математикой %s отнял у монстра %d здоровья.",
      "\"Стой, подожди, не бей, я кое-что попробую!\", сказал %s и ударил монстра на %d урона.",
      "Монстр отбрасывает тень, хвост и %2$d очков здоровья.",
  };

  private static final String[] heroHitAndGetHit = {
      "%s атаковал и нанес %d урона и сам получил %d урона.",
      "%s наносит %d урона, но получает %d в ответ.",
      "%2$d урона туда, %3$d урона обратно.",
      "%s случайно наступил на ногу монстру на %d хп. Чтобы не поссориться монстр наступил в ответ на %d.",
      "Ударил монстра тяжёлым тупым предметом на %2$d хп. Теперь у меня на лбу солидная шишка, -%3$d хп.",
  };

  public static String getText(String name, int damageDone, int damageTaken, boolean heroIsSleep, Random rand) {
    String text;
    if (heroIsSleep) {
      text = heroSleep(name, damageTaken, rand);
    } else {
      if (damageDone == 0) {
        text = heroRun(name, damageTaken, rand);
      } else if (damageDone == -1) {
        text = heroMiss(name, damageTaken, rand);
      } else {
        text = heroHit(name, damageDone, damageTaken, rand);
      }
    }

    return text;
  }

  private static String heroSleep(String name, int damageTaken, Random rand) {
    String text;

    if (damageTaken == 0) {
      text = randText(heroSleepAlone, rand, name);
    } else if (damageTaken == -1) {
      text = randText(heroSleepAndDodge, rand, name);
    } else {
      text = randText(heroSleepAndGetHit, rand, name, damageTaken);
    }

    return text;
  }

  private static String heroRun(String name, int damageTaken, Random rand) {
    String text = "";

    if (damageTaken == -1) {
      text = randText(heroRunAndDodge, rand, name);
    } else if (damageTaken > 0) {
      text = randText(heroRunAndGetHit, rand, name, damageTaken);
    }

    return text;
  }

  private static String heroMiss(String name, int damageTaken, Random rand) {
    String text;

    if (damageTaken <= 0) {
      text = randText(heroMissAlone, rand, name);
    } else {
      text = randText(heroMissAndGetHit, rand, name, damageTaken);
    }

    return text;
  }

  private static String heroHit(String name, int damageDone, int damageTaken, Random rand) {
    String text;

    if (damageTaken <= 0) {
      text = randText(heroHitAlone, rand, name, damageDone);
    } else {
      text = randText(heroHitAndGetHit, rand, name, damageDone, damageTaken);
    }

    return text;
  }

  private static String randText(String[] messages, Random rand, Object... args) {
    String message = messages[rand.nextInt(messages.length)];
    return (args.length > 0) ? String.format(message, args) : message;
  }

  private static final String[] foodText = {
      "Натуральный продукт: без химии, физики и математики. Полечился на %d здоровья.",
      "Нашел загадочную конфету с надписью \"Съешь меня!\". Любопытство победило диету. +%d здоровья.",
      "В древности это блюдо считалось деликатесом. С тех времен оно подпортилось. +%d здоровья.",
      "Подозрительное зелье из бабушкиного погреба. На вкус как компот. +%d здоровья.",
      "Съел что-то странное. Теперь свечусь в темноте, зато здоровее на %d очков!",
      "Нашел банку с надписью: \"Это на новый год\". Не удержался. Восстановил %d здоровья.",
      "В меню новое блюдо: \"404 - название не найдено\". Надо попробовать! +%d здоровья.",
  };

  private static final String[] noFoodText = {
      "На полный желужок в меня уже ничего не лезет, но фантик уже вскрыт, придется выкинуть.",
  };

  public static String getFoodText(int healing, Random rand) {
    String text;

    if (healing == 0) {
      text = randText(noFoodText, rand);
    } else {
      text = randText(foodText, rand, healing);
    }

    return text;
  }
}