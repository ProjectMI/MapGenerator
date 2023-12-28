#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

struct Room {
    int x, y, width, height;
};

struct Corridor {
    int startX, startY, length, direction; // Direction: 0 - вверх, 1 - вправо, 2 - вниз, 3 - влево
};

class DungeonGenerator {
public:
    DungeonGenerator(int numRooms, int mapHeight, int mapWidth, int minRoomSize, int maxRoomSize,
                     int minExits, int maxExits, int minCorridorLength, int maxCorridorLength);
    void generate();
    void printMap();
    void replaceDotsWithHashes();
    void generateWalls();
    void generateRooms();
    void generateDoors(int doorChanceThreshold);
    void fillTiles(const Room& room);
    bool isOverlap(const Room& room) const;
    void generateCorridors();
    void generateCorridorFromRoom(const Room& room);
    void generateCorridor(const Corridor& corridor);
    void connectRooms();
    void generatePath(int startX, int startY, int endX, int endY);

private:
    int numRooms;
    int mapHeight, mapWidth;
    int minRoomSize, maxRoomSize;
    int minExits, maxExits;
    int minCorridorLength, maxCorridorLength;
    std::vector<std::vector<int>> dungeonMap;
    std::vector<Room> rooms;
    std::vector<Corridor> corridors;
};


#endif