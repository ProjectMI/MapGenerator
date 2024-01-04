#pragma once

struct DungeonConfig {
    int numRooms;
    int mapHeight;
    int mapWidth;
    int minRoomSize;
    int maxRoomSize;
    int minExits;
    int maxExits;
    int minCorridorLength;
    int maxCorridorLength;

    DungeonConfig() // Конструктор по умолчанию без параметров
        : numRooms(0), mapHeight(0), mapWidth(0),
        minRoomSize(0), maxRoomSize(0),
        minExits(0), maxExits(0),
        minCorridorLength(0), maxCorridorLength(0)
    {}

    DungeonConfig(int numRooms, int mapHeight, int mapWidth, int minRoomSize, int maxRoomSize,
        int minExits, int maxExits, int minCorridorLength, int maxCorridorLength)
        : numRooms(numRooms), mapHeight(mapHeight), mapWidth(mapWidth),
        minRoomSize(minRoomSize), maxRoomSize(maxRoomSize),
        minExits(minExits), maxExits(maxExits),
        minCorridorLength(minCorridorLength), maxCorridorLength(maxCorridorLength)
    {}
};