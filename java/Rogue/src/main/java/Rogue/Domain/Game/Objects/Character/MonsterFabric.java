package Rogue.Domain.Game.Objects.Character;

import Rogue.Domain.Game.Objects.Room;
import Rogue.Domain.Game.Objects.Character.CharacterEnums.MonsterType;
import Rogue.Domain.Game.Objects.Character.Monsters.Ghost;
import Rogue.Domain.Game.Objects.Character.Monsters.Mimic;
import Rogue.Domain.Game.Objects.Character.Monsters.Ogre;
import Rogue.Domain.Game.Objects.Character.Monsters.SnakeMage;
import Rogue.Domain.Game.Objects.Character.Monsters.Vampire;
import Rogue.Domain.Game.Objects.Character.Monsters.Zombie;
import Rogue.Domain.Game.Utility.Position;

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