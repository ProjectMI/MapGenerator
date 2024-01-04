#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include "mapRenderer.h"
#include "pregenRoom.h"
#include "structs.h"
#include "dungeonConfig.h"


class DungeonGenerator {
public:
    DungeonGenerator(DungeonConfig* config);
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
    void setPregenRoom(const pregenRoom& pregen, int roomCount);
    void pregenRooms();
    const std::vector<std::vector<int>>& getDungeonMap() const;

private:
    DungeonConfig* config;
    MapRenderer* renderer = new MapRenderer;
    pregenRoom pregen;
    std::vector<std::vector<int>> dungeonMap;
    std::vector<Room> rooms;
    std::vector<Corridor> corridors;

};


#endif