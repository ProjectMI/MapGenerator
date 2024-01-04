#ifndef STRUCTS_H
#define STRUCTS_H

struct Room {
    int x, y, width, height;
};

struct Corridor {
    int startX, startY, length, direction; // Direction: 0 - вверх, 1 - вправо, 2 - вниз, 3 - влево
};

#endif