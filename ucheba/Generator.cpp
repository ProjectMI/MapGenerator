#include "Generator.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

DungeonGenerator::DungeonGenerator(int numRooms, int mapHeight, int mapWidth, int minRoomSize, int maxRoomSize,
                                   int minExits, int maxExits, int minCorridorLength, int maxCorridorLength)   :
    numRooms(numRooms), mapHeight(mapHeight), mapWidth(mapWidth), minRoomSize(minRoomSize),
    maxRoomSize(maxRoomSize), minExits(minExits), maxExits(maxExits),
    minCorridorLength(minCorridorLength), maxCorridorLength(maxCorridorLength)
{
    srand(time(nullptr));
    dungeonMap.resize(mapHeight, std::vector<int>(mapWidth, 0));
}

void DungeonGenerator::generate() {
    generateRooms();
    generateCorridors();
    connectRooms();
    replaceDotsWithHashes();
    generateWalls();
}

void DungeonGenerator::printMap() {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            int cellValue = dungeonMap[i][j];

            if (cellValue == 0) {
                std::cout << ' ';  // Решетка
            }
            else if (cellValue == 1) {
                std::cout << '.';  // Тайл
            }
            else if (cellValue == 2) {
                std::cout << 'I';  // Стенка
            }
            else if (cellValue == 3) {
               // std::cout << '';  // Ничего
            }

            std::cout << ' ';
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
                        // Убедитесь, что соседняя клетка находится в пределах карты
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
            dungeonMap[i][j] = 1;
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