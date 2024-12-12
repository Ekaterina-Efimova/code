package Rogue.Domain.Game.Control;

import java.util.Random;

import Rogue.Domain.Game.Objects.Room;
import Rogue.Domain.Game.Objects.Character.Hero;

public class RoomControl {
  private final Random rand;
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
    int first = yRoom * 3 + xRoom;
    int second = first + 1;
    int xStart = rooms[first].x2();
    int yStart = rand.nextInt(rooms[first].y2() - rooms[first].y1() - 1) + rooms[first].y1() + 1;
    int xEnd = rooms[second].x1();
    int yEnd = rand.nextInt(rooms[second].y2() - rooms[second].y1() - 1) + rooms[second].y1() + 1;
    int crossLine = rand.nextInt(xEnd - xStart - 1) + xStart + 1;
    asciiMap[yStart][xStart] = '+';
    asciiMap[yEnd][xEnd] = '+';
    addHorizontalLine(asciiMap, xStart + 1, crossLine + 1, yStart);
    addVerticalLine(asciiMap, yStart, yEnd, crossLine);
    addHorizontalLine(asciiMap, crossLine, xEnd, yEnd);
  }

  private void addVerticalCorridor(char[][] asciiMap, int xRoom, int yRoom) {
    int first = yRoom * 3 + xRoom;
    int second = first + 3;
    int xStart = rand.nextInt(rooms[first].x2() - rooms[first].x1() - 1) + rooms[first].x1() + 1;
    int yStart = rooms[first].y2();
    int xEnd = rand.nextInt(rooms[second].x2() - rooms[second].x1() - 1) + rooms[second].x1() + 1;
    int yEnd = rooms[second].y1();
    int crossLine = rand.nextInt(yEnd - yStart - 1) + yStart + 1;
    asciiMap[yStart][xStart] = '+';
    asciiMap[yEnd][xEnd] = '+';
    addVerticalLine(asciiMap, yStart + 1, crossLine + 1, xStart);
    addHorizontalLine(asciiMap, xStart, xEnd, crossLine);
    addVerticalLine(asciiMap, crossLine, yEnd, xEnd);
  }

  private void addHorizontalLine(char[][] asciiMap, int from, int where, int y) {
    int start = Math.min(from, where);
    int end = Math.max(from, where);
    for (int x = start; x < end; x++) {
      asciiMap[y][x] = '#';
    }
  }

  private void addVerticalLine(char[][] asciiMap, int from, int where, int x) {
    int start = Math.min(from, where);
    int end = Math.max(from, where);
    for (int y = start; y < end; y++) {
      asciiMap[y][x] = '#';
    }
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

    asciiMap[exitY][exitX] = '⇧';
  }

  public Room[] getRooms() {
    return rooms;
  }
}