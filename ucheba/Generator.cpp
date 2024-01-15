#include "Generator.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "mapRenderer.h"
#include "pregenRoom.h"
#include "dungeonConfig.h"

DungeonGenerator::DungeonGenerator(DungeonConfig* config)   :
    config(config), pregen(pregen)
{
    srand(1);
    dungeonMap.resize(config->mapHeight, std::vector<int>(config->mapWidth, 0));
    
}

void DungeonGenerator::generate() {
    generateRooms();
    generateCorridors();
    connectRooms();
    //pregenRooms();
    replaceDotsWithHashes();
    generateWalls();
    generateDoors(45);
    
}

//Сюда спихиваем все комнаты которые хотим загенерить
void DungeonGenerator::pregenRooms() {
    setPregenRoom(pregen.room1(), 3);
    setPregenRoom(pregen.room2(), 3);
}

void DungeonGenerator::printMap() {
    for (int i = 0; i < config->mapHeight; ++i) {
        for (int j = 0; j < config->mapWidth; ++j) {
            int cellValue = dungeonMap[i][j];

            renderer->setConsoleColor(cellValue);
            renderer->renderCell(cellValue);
            renderer->resetConsoleColor();
        }
        std::cout << std::endl;
    }
}



void DungeonGenerator::replaceDotsWithHashes() {
    // Перебираем верхнюю и нижнюю границы карты
    for (int i = 0; i < config->mapWidth; ++i) {
        if (dungeonMap[0][i] == 1) {
            dungeonMap[0][i] = 2;  // Заменяем точку на другое значение (например, 0), представляющее стенку
        }
        if (dungeonMap[config->mapHeight - 1][i] == 1) {
            dungeonMap[config->mapHeight - 1][i] = 2;  // Заменяем точку на другое значение (например, 0), представляющее стенку
        }
    }

    // Перебираем левую и правую границы карты
    for (int i = 0; i < config->mapHeight; ++i) {
        if (dungeonMap[i][0] == 1) {
            dungeonMap[i][0] = 2;  // Заменяем точку на другое значение (например, 0), представляющее стенку
        }
        if (dungeonMap[i][config->mapWidth - 1] == 1) {
            dungeonMap[i][config->mapWidth - 1] = 2;  // Заменяем точку на другое значение (например, 0), представляющее стенку
        }
    }
}

void DungeonGenerator::generateWalls() {
    for (int i = 0; i < config->mapHeight; ++i) {
        for (int j = 0; j < config->mapWidth; ++j) {
            if (dungeonMap[i][j] == 0) {  // Проверяем, если текущая ячейка представляет собой решетку
                bool hasHorizontalNeighbor = false;
                bool hasVerticalNeighbor = false;
                bool hasDiagonalNeighbor = false;  // Добавляем проверку на диагонального соседа

                // Проверяем все соседние клетки, включая диагонали
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        // Нужно убедиться, что соседняя клетка находится в пределах карты
                        int ni = i + dx;
                        int nj = j + dy;

                        if (ni >= 0 && ni < config->mapHeight && nj >= 0 && nj < config->mapWidth) {
                            if (dx == 0 && dy == 0)
                                continue;  // Пропускаем текущую ячейку

                            if (dungeonMap[ni][nj] == 1) {
                                if (dx == 0 || dy == 0) {
                                    // Горизонтальный или вертикальный сосед
                                    if (dx != 0) {
                                        hasHorizontalNeighbor = true;
                                    }
                                    else {
                                        hasVerticalNeighbor = true;
                                    }
                                }
                                else {
                                    // Диагональный сосед
                                    hasDiagonalNeighbor = true;
                                }
                            }
                        }
                    }
                }

                // Определяем тип стены и устанавливаем соответствующее значение в карту
                if (hasHorizontalNeighbor && hasVerticalNeighbor) {
                    dungeonMap[i][j] = 10;  // Угловая стена
                }
                else if (hasHorizontalNeighbor && !hasVerticalNeighbor) {
                    dungeonMap[i][j] = 11;  // Горизонтальная стена
                }
                else if (!hasHorizontalNeighbor && hasVerticalNeighbor) {
                    dungeonMap[i][j] = 12;  // Вертикальная стена
                }
                else if (hasDiagonalNeighbor) {
                    dungeonMap[i][j] = 10;  // Угловая стена
                }
            }
        }
    }
}



void DungeonGenerator::generateDoors(int doorChanceThreshold) {
    for (int i = 1; i < config->mapHeight - 1; ++i) {
        for (int j = 1; j < config->mapWidth - 1; ++j) {
            if (dungeonMap[i][j] == 1) {  // Проверяем, если текущая ячейка представляет собой тайл
                bool hasVerticalWall = (dungeonMap[i - 1][j] == 10 && dungeonMap[i + 1][j] == 10);
                bool hasHorizontalWall = (dungeonMap[i][j - 1] == 10 && dungeonMap[i][j + 1] == 10);
                int tileCount = 0;

                // Подсчет окружающих тайлов в каждом направлении
                int leftTileCount = 0, rightTileCount = 0, upTileCount = 0, downTileCount = 0;
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx != 0 || dy != 0) {  // Исключаем текущую ячейку
                            if (dungeonMap[i + dx][j + dy] == 1) {
                                tileCount++;
                                // Подсчет тайлов в каждом направлении
                                if (dx == -1) leftTileCount++;
                                else if (dx == 1) rightTileCount++;
                                if (dy == -1) upTileCount++;
                                else if (dy == 1) downTileCount++;
                            }
                            else if (dungeonMap[i + dx][j + dy] == 3) {
                                break;
                            }
                        }
                    }
                }

                // Проверяем условия для генерации двери
                if ((hasVerticalWall && !hasHorizontalWall && (upTileCount > 0 || downTileCount > 0)) ) {
                    if (tileCount > 3) {
                        int randomChance = std::rand() % 100; // бросаем кубики на создание двери
                        if (randomChance < doorChanceThreshold) {
                            dungeonMap[i][j] = 3;  // Меняем тайл на дверь горизонтальная
                        }
                        
                    }
                }

                if (hasHorizontalWall && !hasVerticalWall && (leftTileCount > 0 || rightTileCount > 0)) {
                    if (tileCount > 3) {
                        int randomChance = std::rand() % 100; // бросаем кубики на создание двери
                        if (randomChance < doorChanceThreshold) {
                            dungeonMap[i][j] = 4;  // Меняем тайл на дверь вертикальная
                        }

                    }
                }
            }
        }
    }
}

void DungeonGenerator::generateRooms() {
    for (int i = 0; i < config->numRooms; ++i) {
        int roomWidth = rand() % (config->maxRoomSize - config->minRoomSize + 1) + config->minRoomSize;
        int roomHeight = rand() % (config->maxRoomSize - config->minRoomSize + 1) + config->minRoomSize;
        int x = rand() % (config->mapWidth - roomWidth);
        int y = rand() % (config->mapHeight - roomHeight);

        Room room = { x, y, roomWidth, roomHeight };
        if (isOverlap(room)) {
            --i;
            continue;
        }

        rooms.push_back(room);
        fillTiles(room);
    }
}

void DungeonGenerator::fillTiles(const Room& room) {
    for (int i = room.y; i < room.y + room.height; ++i) {
        for (int j = room.x; j < room.x + room.width; ++j) {
            dungeonMap[i][j] = 1; // заливаем пространство тайлами
        }
    }
}

bool DungeonGenerator::isOverlap(const Room& room) const {
    for (const auto& existingRoom : rooms) {
        if (room.x < existingRoom.x + existingRoom.width &&
            room.x + room.width > existingRoom.x &&
            room.y < existingRoom.y + existingRoom.height &&
            room.y + room.height > existingRoom.y) {
            return true;
        }
    }
    return false;
}

void DungeonGenerator::generateCorridors() {
    for (const auto& room : rooms) {
        int numExits = rand() % (config->maxExits - config->minExits + 1) + config->minExits;
        for (int i = 0; i < numExits; ++i) {
            generateCorridorFromRoom(room);
        }
    }
}

void DungeonGenerator::generateCorridorFromRoom(const Room& room) {
    int startX = room.x + rand() % room.width;
    int startY = room.y + rand() % room.height;
    int length = rand() % (config->maxCorridorLength - config->minCorridorLength + 1) + config->minCorridorLength;
    int direction = rand() % 4;

    Corridor corridor = { startX, startY, length, direction };
    generateCorridor(corridor);
}

void DungeonGenerator::generateCorridor(const Corridor& corridor) {
    int x = corridor.startX;
    int y = corridor.startY;

    for (int i = 0; i < corridor.length; ++i) {
        if (x >= 0 && x < config->mapWidth && y >= 0 && y < config->mapHeight) {
            dungeonMap[y][x] = 1;
        }

        switch (corridor.direction) {
        case 0: // Вверх
            --y;
            break;
        case 1: // Вправо
            ++x;
            break;
        case 2: // Вниз
            ++y;
            break;
        case 3: // Влево
            --x;
            break;
        }
    }
}

void DungeonGenerator::connectRooms() {
    std::random_shuffle(rooms.begin(), rooms.end());

    for (size_t i = 1; i < rooms.size(); ++i) {
        int startX = rooms[i].x + rooms[i].width / 2;
        int startY = rooms[i].y + rooms[i].height / 2;
        int endX = rooms[i - 1].x + rooms[i - 1].width / 2;
        int endY = rooms[i - 1].y + rooms[i - 1].height / 2;

        generatePath(startX, startY, endX, endY);
    }
}

void DungeonGenerator::generatePath(int startX, int startY, int endX, int endY) {
    int currentX = startX;
    int currentY = startY;

    while (currentX != endX) {
        if (currentX < endX) {
            ++currentX;
        }
        else if (currentX > endX) {
            --currentX;
        }

        if (currentX >= 0 && currentX < config->mapWidth && currentY >= 0 && currentY < config->mapHeight) {
            dungeonMap[currentY][currentX] = 1;
        }
    }

    while (currentY != endY) {
        if (currentY < endY) {
            ++currentY;
        }
        else if (currentY > endY) {
            --currentY;
        }

        if (currentX >= 0 && currentX < config->mapWidth && currentY >= 0 && currentY < config->mapHeight) {
            dungeonMap[currentY][currentX] = 1;
        }
    }
}

void DungeonGenerator::setPregenRoom(const pregenRoom& pregen, int roomCount) {
    for (int i = 0; i < roomCount; ++i) {
        const std::vector<std::vector<int>>& roomLayout = pregen.getLayout();

        // Получаем размеры комнаты и карты
        int roomHeight = roomLayout.size();
        int roomWidth = roomLayout[0].size();

        // Переменные для хранения координат вставки комнаты
        int startX, startY;

        // Флаг для обозначения успешности вставки комнаты
        bool roomInserted = false;

        int attempts = 0; // Счетчик попыток вставки комнаты
        int maxAttempts = 1500; // Максимальное количество циклов для одной вставки

        // Перебираем случайные координаты, пока не найдем подходящее место
        while (!roomInserted && attempts < maxAttempts) {
            startX = rand() % (config->mapWidth - roomWidth + 1);
            startY = rand() % (config->mapHeight - roomHeight + 1);

            // Проверяем, есть ли достаточно свободного места для вставки комнаты
            bool canPlaceRoom = true;
            for (int x = startX; x < startX + roomWidth; ++x) {
                for (int y = startY; y < startY + roomHeight; ++y) {
                    if (dungeonMap[y][x] != 1) { // Выбираем тип поверхности, на который будет делать проверку, в нашем случае это тайл
                        canPlaceRoom = false; // Если хоть один тайл уже занят, то помечаем, что не можем разместить комнату
                        break;
                    }
                }
                if (!canPlaceRoom) {
                    break;
                }
            }

            // Если есть достаточно свободного места, вставляем комнату в карту
            if (canPlaceRoom) {
                // Дополнительная проверка на свободное место, учитывая площадь всей комнаты
                int requiredFreeSpace = roomWidth * roomHeight;
                for (int x = startX; x < startX + roomWidth; ++x) {
                    for (int y = startY; y < startY + roomHeight; ++y) {
                        if (dungeonMap[y][x] != 1) { // Если тайл уже занят, уменьшаем необходимую свободную площадь
                            requiredFreeSpace--;
                        }
                    }
                }
                if (requiredFreeSpace <= 0) { // Если свободной площади не хватает, не вставляем комнату
                    canPlaceRoom = false;
                }

                if (canPlaceRoom) {
                    // Вставляем комнату в карту
                    for (int x = 0; x < roomWidth; ++x) {
                        for (int y = 0; y < roomHeight; ++y) {
                            dungeonMap[startY + y][startX + x] = roomLayout[y][x];
                        }
                    }
                    roomInserted = true;
                }
            }
            attempts++;
        }
    }
}

const std::vector<std::vector<int>>& DungeonGenerator::getDungeonMap() const {
    return dungeonMap;
}