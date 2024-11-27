package Domain.Character.Monsters;

import Domain.Character.Control.Character;
import Domain.Game.Objects.Room;
import Domain.Utility.Position;
import Domain.Character.CharacterEnums.MonsterType;

import java.util.Random;

public class MonsterFabric {
  private MonsterFabric() {
  }

  public static Character createMonster(Position position, Room room, int floor) {
    MonsterType monsterType = MonsterType.random();

    Character monster;
    if (monsterType == MonsterType.ZOMBIE) {
      monster = new Zombie();
    } else if (monsterType == MonsterType.VAMPIRE) {
      monster = new Vampire();
    } else if (monsterType == MonsterType.GHOST) {
      monster = new Ghost();
    } else if (monsterType == MonsterType.OGRE) {
      monster = new Ogre();
    } else if (monsterType == MonsterType.SNAKE_MAGE) {
      monster = new SnakeMage();
    } else {
      monster = new Mimic();
    }
    monster.setPosition(position);
    monster.setRoom(room);
    monster.addFloorDifficulty(floor);

    return monster;
  }
}

