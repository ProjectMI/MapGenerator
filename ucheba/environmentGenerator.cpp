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
    fillTorchesAndIvys();

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

void EnvironmentGenerator::fillTorchesAndIvys() {
    for (int i = 0; i < config->mapHeight; ++i) {
        for (int j = 0; j < config->mapWidth; ++j) {

            if (dungeonMap[i][j] == 11) {               // �������������� ����� �����
                generateTorchesAndIvys(i, j, 100);
            }

            if (dungeonMap[i][j] == 12) {               // �������������� ����� ����
                generateTorchesAndIvys(i, j, 100);
            }

            if (dungeonMap[i][j] == 13) {               // ������������ ����� �����
                generateTorchesAndIvys(i, j, 100);
            }

            if (dungeonMap[i][j] == 14) {               // ������������ ����� ����
                generateTorchesAndIvys(i, j, 100);
            }
        }
    }
}

void EnvironmentGenerator::generateTorchesAndIvys(int i, int j, int generateChanceTheshold) {
    int randomForSpawn = std::rand() % 100; // ������� ������ �� �������� ������ � ���������� ���������
    int randomForTorches = std::rand() % 100;
    int torchSpawnTreshold = 15;
    if (randomForSpawn < generateChanceTheshold) {
        
        if (randomForTorches < torchSpawnTreshold) {
            environmentMap[i][j] = 1; // ������ �����
        }
        else {
            int randomForIvysAndTorches = std::rand() % 100;
            int onlyIvysSpawnTreshold = 85;

            if (randomForIvysAndTorches < onlyIvysSpawnTreshold) {
                int chanceForProps = std::rand() % 2;
                switch (chanceForProps) {
                    case 0: {
                        environmentMap[i][j] = 5; // ������ �����
                        break;
                    }
                    case 1: {
                        environmentMap[i][j] = 6; // 2 �����
                        break;
                    }
                    case 2: {
                        environmentMap[i][j] = 7; // 3 �����
                        break;
                    }
                }
            }
            else {
                int chanceForProps = std::rand() % 2;
                switch (chanceForProps) {
                    case 0: {
                        environmentMap[i][j] = 2; // ����� + �����
                        break;
                    }
                    case 1: {
                        environmentMap[i][j] = 3; // ����� + 2 �����
                        break;
                    }
                    case 2: {
                        environmentMap[i][j] = 4; // ����� + 3 �����
                        break;
                    }
                }
            }
        }
    }
}




