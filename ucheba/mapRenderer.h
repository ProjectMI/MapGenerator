#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H

class MapRenderer {
public:
    char getSymbolForCellValue(int cellValue);
    void renderCell(int cellValue);
    void setConsoleColor(int cellValue);
    void resetConsoleColor();
};

#endif