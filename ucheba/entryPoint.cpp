#include "Generator.h"

int main() {
    DungeonGenerator generator(15, 60, 60, 6, 15, 0, 5, 0, 5);
    generator.generate();
    generator.printMap();

    return 0;
}
