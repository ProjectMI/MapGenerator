#include "environmentGenerator.h"
#include "Generator.h"
#include <iostream>
#include <vector>

EnvironmentGenerator::EnvironmentGenerator(DungeonGenerator* dungeonGenerator, DungeonConfig* config) :
    config(config), dungeonGenerator(new DungeonGenerator(config))
{
    environmentMap.resize(config->mapHeight, std::vector<int>(config->mapWidth, 0));
    dungeonMap = dungeonGenerator->getDungeonMap();
}


void EnvironmentGenerator::generate() {

}