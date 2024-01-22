#ifndef ENVGENERATOR_H
#define ENVGENERATOR_H

#include "Generator.h"
#include "environmentRenderer.h"

class EnvironmentGenerator {
public:
    EnvironmentGenerator(DungeonGenerator* dungeonGenerator, DungeonConfig* config);
    void generate();
    void printDungeonMap(const std::vector<std::vector<int>>& environmentMap);
    void fillTorchesAndIvys();
    void generateTorchesAndIvys(int i, int j, int generateChanceTheshold);


private:
    environmentRenderer* renderer = new environmentRenderer;
    DungeonGenerator* dungeonGenerator;
    DungeonConfig* config;
    std::vector<std::vector<int>> environmentMap;
    std::vector<std::vector<int>> dungeonMap;
};


#endif