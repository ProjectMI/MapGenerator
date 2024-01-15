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
    for (int i = 1; i < config->mapHeight - 1; ++i) {
        for (int j = 1; j < config->mapWidth - 1; ++j) {
            if (dungeonMap[i][j] == 1) { // если встречаем тайл (1), то ставим предмет
                int item = 1 + rand() % 9;
                environmentMap[i][j] = item;
            }
        }
    }
    for (int i = 0; i < config->mapHeight; ++i) {
        for (int j = 0; j < config->mapWidth; ++j) {
            int cellValue = environmentMap[i][j];

            renderer->setConsoleColor(cellValue);
            renderer->renderCell(cellValue);
            renderer->resetConsoleColor();
        }
        std::cout << std::endl;
    }

}

void EnvironmentGenerator::printDungeonMap(const std::vector<std::vector<int>>& environmentMap) {
    for (size_t i = 0; i < environmentMap.size(); ++i) {
        for (size_t j = 0; j < environmentMap[i].size(); ++j) {
            std::cout << environmentMap[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}