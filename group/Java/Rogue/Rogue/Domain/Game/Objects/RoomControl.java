package Domain.Game.Objects;

import java.util.Random;

import Domain.Character.Control.Hero;

public class RoomControl {
  private Random rand;
  private Room[] rooms;

  public RoomControl(Random rand) {
    this.rand = rand;
    rooms = new Room[9];
  }

  public void addFillRoomsOnMap(char[][] asciiMap, Hero player) {
    generateRooms();
    addRoomsOnMap(asciiMap);
    addCorridorsOnMap(asciiMap);
    fillRooms(asciiMap, player);
  }

  private void addRoomsOnMap(char[][] asciiMap) {
    for (int i = 0; i < 9; i++) {
      for (int x = rooms[i].x1(); x < rooms[i].x2(); x++) {
        asciiMap[rooms[i].y1()][x] = '—';
        asciiMap[rooms[i].y2()][x] = '—';
      }

      for (int y = rooms[i].y1(); y <= rooms[i].y2(); y++) {
        asciiMap[y][rooms[i].x1()] = '|';
        asciiMap[y][rooms[i].x2()] = '|';
      }
    }

    for (int i = 0; i < 9; i++) {
      for (int x = rooms[i].x1() + 1; x < rooms[i].x2(); x++) {
        for (int y = rooms[i].y1() + 1; y < rooms[i].y2(); y++) {
          asciiMap[y][x] = '·';
        }
      }
    }
  }

  private void generateRooms() {
    rooms = new Room[9];

    int count = 0;
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 3; x++) {
        rooms[count++] = new Room(x, y);
      }
    }
  }

  private void addCorridorsOnMap(char[][] asciiMap) {
    for (int yRoom = 0; yRoom < 3; yRoom++) {
      for (int xRoom = 0; xRoom < 3; xRoom++) {
        if (xRoom < 2) {
          addHorizontalCorridor(asciiMap, xRoom, yRoom);
        }
        if (yRoom < 2) {
          addVerticalCorridor(asciiMap, xRoom, yRoom);
        }
      }
    }
  }

  private void addHorizontalCorridor(char[][] asciiMap, int xRoom, int yRoom) {
    int yGlobal = calcGlobal(yRoom, Room.SECTOR_HEIGHT);
    int start = rooms[yRoom * 3 + xRoom].x2();
    int end = rooms[yRoom * 3 + xRoom + 1].x1();
    asciiMap[yGlobal][start] = '+';
    asciiMap[yGlobal][end] = '+';
    for (int x = start + 1; x < end; x++) {
      asciiMap[yGlobal][x] = '#';
    }
  }

  private void addVerticalCorridor(char[][] asciiMap, int xRoom, int yRoom) {
    int xGlobal = calcGlobal(xRoom, Room.SECTOR_WIDTH);
    int start = rooms[yRoom * 3 + xRoom].y2();
    int end = rooms[(yRoom + 1) * 3 + xRoom].y1();
    asciiMap[start][xGlobal] = '+';
    asciiMap[end][xGlobal] = '+';
    for (int y = start + 1; y < end; y++) {
      asciiMap[y][xGlobal] = '#';
    }
  }

  private int calcGlobal(int roomIndex, int sectorSize) {
    return (sectorSize / 2) + roomIndex * (sectorSize + 1);
  }

  private void fillRooms(char[][] asciiMap, Hero player) {
    setStartRoom(player);
    setExitRoom(asciiMap);
  }

  private void setStartRoom(Hero player) {
    int sRoom = rand.nextInt(9);
    rooms[sRoom].setStartRoom();

    int playerX = rand.nextInt(rooms[sRoom].x2() - rooms[sRoom].x1() - 1) + rooms[sRoom].x1() + 1;
    int playerY = rand.nextInt(rooms[sRoom].y2() - rooms[sRoom].y1() - 1) + rooms[sRoom].y1() + 1;
    player.setPosition(playerX, playerY);
  }

  private void setExitRoom(char[][] asciiMap) {
    int endRoom;
    do {
      endRoom = rand.nextInt(9);
    } while (rooms[endRoom].isStartRoom());
    int exitX = rand.nextInt(rooms[endRoom].x2() - rooms[endRoom].x1() - 1) + rooms[endRoom].x1() + 1;
    int exitY = rand.nextInt(rooms[endRoom].y2() - rooms[endRoom].y1() - 1) + rooms[endRoom].y1() + 1;
    rooms[endRoom].setExitRoom();

    asciiMap[exitY][exitX] = '⇧';
  }

  public Room[] getRooms() {
    return rooms;
  }
}
