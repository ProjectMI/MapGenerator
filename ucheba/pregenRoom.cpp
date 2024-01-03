#include "pregenRoom.h"

pregenRoom::pregenRoom(std::vector<std::vector<int>> layout) : layout(layout) {}

std::vector<std::vector<int>> pregenRoom::getLayout() const {
    return layout;
}

//Вариация для комнаты в виде матрицы
pregenRoom pregenRoom::room1() {
    return pregenRoom({
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 3, 3, 3, 3, 3, 3, 2, 1},
    {1, 2, 3, 4, 4, 4, 4, 3, 2, 1},
    {1, 2, 3, 4, 6, 4, 4, 3, 2, 1},
    {1, 2, 3, 4, 7, 4, 4, 3, 2, 1},
    {1, 2, 3, 4, 8, 4, 4, 3, 2, 1},
    {1, 2, 2, 2, 5, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        });
}

pregenRoom pregenRoom::room2() {
    return pregenRoom({
        // Другие параметры для room2
        });
}