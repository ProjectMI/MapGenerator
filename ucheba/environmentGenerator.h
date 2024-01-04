#ifndef ENVGENERATOR_H
#define ENVGENERATOR_H

#include "Generator.h"

class EnvironmentGenerator {
public:
    EnvironmentGenerator(DungeonGenerator* dungeonGenerator, DungeonConfig* config);
    void generate();


private:
    DungeonGenerator* dungeonGenerator;
    DungeonConfig* config;
    std::vector<std::vector<int>> environmentMap;
    std::vector<std::vector<int>> dungeonMap;
};


#endif