#ifndef FIRSTENUM_H
#define FIRSTENUM_H

enum class TileSymbols {
    Void = 0,
    Tile = 1,
    Wall = 2,
    HorizontDoor = 3,
    VertDoor = 4,
    AngleWall = 10,
    HorizontWallUp = 11,
    HorizontWallDown = 12,
    VertWallRight = 13,
    VertWallLeft = 14
};

// Оператор приведения к типу int вне определения перечисления
inline int to(TileSymbols value) {
    return static_cast<int>(value);
}



#endif 