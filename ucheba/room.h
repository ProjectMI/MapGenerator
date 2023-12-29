#ifndef ROOM_H
#define ROOM_H

#include <vector>

class pregenRoom {
public:
    pregenRoom(std::vector<std::vector<int>> layout);
    std::vector<std::vector<int>> getLayout() const;
    static pregenRoom room1();
    static pregenRoom room2();

private:
    std::vector<std::vector<int>> layout;
};

#endif