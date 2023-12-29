#include "room.h"

pregenRoom::pregenRoom(std::vector<std::vector<int>> layout) : layout(layout) {}

std::vector<std::vector<int>> pregenRoom::getLayout() const {
    return layout;
}

//Вариация для комнаты в виде матрицы
pregenRoom pregenRoom::room1() {
    return pregenRoom({
        {2, 2, 2, 2, 2},
        {2, 1, 1, 1, 2},
        {2, 1, 0, 1, 2},
        {2, 1, 1, 1, 2},
        {2, 2, 2, 2, 2}
        });
}

pregenRoom pregenRoom::room2() {
    return pregenRoom({
        // Другие параметры для room2
        });
}