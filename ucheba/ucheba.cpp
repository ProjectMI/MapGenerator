#include "Generator.h"

int main() {
    DungeonGenerator generator(30, 60, 60, 3, 15, 0, 5, 0, 5);
    generator.generate();
    generator.printMap();

    return 0;
}
