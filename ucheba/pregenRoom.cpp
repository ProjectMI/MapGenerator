#include "pregenRoom.h"

pregenRoom::pregenRoom(std::vector<std::vector<int>> layout) : layout(layout) {}

std::vector<std::vector<int>> pregenRoom::getLayout() const {
    return layout;
}

//¬ариаци¤ дл¤ комнаты в виде матрицы
pregenRoom pregenRoom::room1() {
    return pregenRoom({
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 3, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 2, 1},
        {1, 3, 1, 1, 1, 1, 1, 3, 1},
        {1, 2, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 3, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1}
        });
}

pregenRoom pregenRoom::room2() {
    return pregenRoom({
        // ƒругие параметры дл¤ room2
        });
}