#ifndef ENVIRONMENT_RENDERER_H
#define ENVIRONMENT_RENDERER_H

class environmentRenderer {
public:
    char getSymbolForCellValue(int cellValue);
    void renderCell(int cellValue);
    void setConsoleColor(int cellValue);
    void resetConsoleColor();
};

#endif