#include "Generator.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "mapRenderer.h"
#include "pregenRoom.h"

DungeonGenerator::DungeonGenerator(int numRooms, int mapHeight, int mapWidth, int minRoomSize, int maxRoomSize,
                                   int minExits, int maxExits, int minCorridorLength, int maxCorridorLength)   :
    numRooms(numRooms), mapHeight(mapHeight), mapWidth(mapWidth), minRoomSize(minRoomSize),
    maxRoomSize(maxRoomSize), minExits(minExits), maxExits(maxExits),
    minCorridorLength(minCorridorLength), maxCorridorLength(maxCorridorLength), pregen(pregen)
{
    srand(time(nullptr));
    dungeonMap.resize(mapHeight, std::vector<int>(mapWidth, 0));
}

void DungeonGenerator::generate() {
    generateRooms();
    generateCorridors();
    connectRooms();
    setPregenRoom(pregen.room1(), 3);
    setPregenRoom(pregen.room2(), 3);
    replaceDotsWithHashes();
    generateWalls();
    generateDoors(45);
    
}

void DungeonGenerator::printMap() {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
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
    for (int i = 0; i < mapWidth; ++i) {
        if (dungeonMap[0][i] == 1) {
            dungeonMap[0][i] = 2;  // Заменяем точку на другое значение (например, 0), представляющее стенку
        }
        if (dungeonMap[mapHeight - 1][i] == 1) {
            dungeonMap[mapHeight - 1][i] = 2;  // Заменяем точку на другое значение (например, 0), представляющее стенку
        }
    }

    // Перебираем левую и правую границы карты
    for (int i = 0; i < mapHeight; ++i) {
        if (dungeonMap[i][0] == 1) {
            dungeonMap[i][0] = 2;  // Заменяем точку на другое значение (например, 0), представляющее стенку
        }
        if (dungeonMap[i][mapWidth - 1] == 1) {
            dungeonMap[i][mapWidth - 1] = 2;  // Заменяем точку на другое значение (например, 0), представляющее стенку
        }
    }
}

void DungeonGenerator::generateWalls() {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (dungeonMap[i][j] == 0) {  // Проверяем, если текущая ячейка представляет собой решетку
                // Проверяем все соседние клетки, включая диагонали
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        // Нужно убедиться, что соседняя клетка находится в пределах карты
                        int ni = i + dx;
                        int nj = j + dy;

                        if (ni >= 0 && ni < mapHeight && nj >= 0 && nj < mapWidth) {
                            if (dungeonMap[ni][nj] == 1) {
                                dungeonMap[i][j] = 2;  // Меняем решетку на стенку (например 2, нужно будет подумать стоит ли менять магические числа)
                                break;  // Прекращаем проверку при первом обнаружении соседней тайловой клетки
                            }
                        }
                    }
                    if (dungeonMap[i][j] == 2) {
                        break;  // Прекращаем проверку, если уже заменили решетку на стенку
                    }
                }
            }
        }
    }
}

void DungeonGenerator::generateDoors(int doorChanceThreshold) {
    for (int i = 1; i < mapHeight - 1; ++i) {
        for (int j = 1; j < mapWidth - 1; ++j) {
            if (dungeonMap[i][j] == 1) {  // Проверяем, если текущая ячейка представляет собой тайл
                bool hasVerticalWall = (dungeonMap[i - 1][j] == 2 && dungeonMap[i + 1][j] == 2);
                bool hasHorizontalWall = (dungeonMap[i][j - 1] == 2 && dungeonMap[i][j + 1] == 2);
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
                if ((hasVerticalWall && !hasHorizontalWall && (upTileCount > 0 || downTileCount > 0)) ||
                    (hasHorizontalWall && !hasVerticalWall && (leftTileCount > 0 || rightTileCount > 0))) {
                    if (tileCount > 3) {
                        int randomChance = std::rand() % 100; // бросаем кубики на создание двери
                        if (randomChance < doorChanceThreshold) {
                            dungeonMap[i][j] = 3;  // Меняем тайл на дверь (например, 3, нужно будет подумать стоит ли менять магические числа)
                        }
                        
                    }
                }
            }
        }
    }
}

void DungeonGenerator::generateRooms() {
    for (int i = 0; i < numRooms; ++i) {
        int roomWidth = rand() % (maxRoomSize - minRoomSize + 1) + minRoomSize;
        int roomHeight = rand() % (maxRoomSize - minRoomSize + 1) + minRoomSize;
        int x = rand() % (mapWidth - roomWidth);
        int y = rand() % (mapHeight - roomHeight);

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
        int numExits = rand() % (maxExits - minExits + 1) + minExits;
        for (int i = 0; i < numExits; ++i) {
            generateCorridorFromRoom(room);
        }
    }
}

void DungeonGenerator::generateCorridorFromRoom(const Room& room) {
    int startX = room.x + rand() % room.width;
    int startY = room.y + rand() % room.height;
    int length = rand() % (maxCorridorLength - minCorridorLength + 1) + minCorridorLength;
    int direction = rand() % 4;

    Corridor corridor = { startX, startY, length, direction };
    generateCorridor(corridor);
}

void DungeonGenerator::generateCorridor(const Corridor& corridor) {
    int x = corridor.startX;
    int y = corridor.startY;

    for (int i = 0; i < corridor.length; ++i) {
        if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
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

        if (currentX >= 0 && currentX < mapWidth && currentY >= 0 && currentY < mapHeight) {
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

        if (currentX >= 0 && currentX < mapWidth && currentY >= 0 && currentY < mapHeight) {
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
            startX = rand() % (mapWidth - roomWidth + 1);
            startY = rand() % (mapHeight - roomHeight + 1);

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