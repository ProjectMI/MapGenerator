#include "mapRenderer.h"
#include <iostream>

    char MapRenderer::getSymbolForCellValue(int cellValue) {
        switch (cellValue) {
        case 0:
            return ' ';  // Решетка
        case 1:
            return '.';  // Тайл
        case 2:
            return 'I';  // Стенка
        case 3:
            return 'H';  // Дверь
        default:
            return ' ';  // По умолчанию, например, для неизвестных значений
        }
    }

    void MapRenderer::renderCell(int cellValue) {
        std::cout << getSymbolForCellValue(cellValue);
    }

    void MapRenderer::setConsoleColor(int cellValue) {
        std::string colorCode = "";
        switch (cellValue) {
        case 2:
            // Стенка (желтый)
            colorCode = "\033[38;5;226m";
            break;
        case 1:
            // Тайл (зеленый)
            colorCode = "\033[38;5;34m";
            break;
        case 3:
            // Дверь (красный)
            colorCode = "\033[38;5;196m";
            break;
        default:
            // Стандартный цвет
            colorCode = "\033[0m";
            break;
        }

        std::cout << colorCode;
    }

    void MapRenderer::resetConsoleColor() {
        std::cout << "\033[0m ";  // Сброс цвета
    }
