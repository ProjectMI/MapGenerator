#include "Generator.h"
#include "dungeonConfig.h"
#include "environmentGenerator.h"

int main() {
    DungeonConfig* config = new DungeonConfig(15, 60, 60, 6, 15, 0, 5, 0, 5);
    DungeonGenerator generator(config);
    generator.generate();
    generator.printMap();
    EnvironmentGenerator EnvironmentGenerator(&generator, config); //сюда явно передаем объект генератора, без не получим карту генерации
    return 0;
}
