#include "environmentRenderer.h"
#include <iostream>

char environmentRenderer::getSymbolForCellValue(int cellValue) {
    switch (cellValue) {
    default:
        return ' ';  // По умолчанию, например, для неизвестных значений
    case 1:
        return '$';  // Сундук
    case 2:
        return 't';  // Стол
    case 3:
        return 'c';  // Стул
    case 4:
        return 'f';  // фонтан
    case 5:
        return '^'; // фонарь
    case 6:
        return '%'; // хз че
    case 7:
        return '+'; // плюсик
    case 8:
        return '-'; // минусик
    case 9:
        return '@'; // собака 
    case 10:
        return '!'; // человечек 
    }
}

void environmentRenderer::renderCell(int cellValue) {
    std::cout << getSymbolForCellValue(cellValue);
}

void environmentRenderer::setConsoleColor(int cellValue) {
    std::string colorCode = "";
    switch (cellValue) {
    default:
        // Стандартный цвет
        colorCode = "\033[0m";
        break;
    case 1:
        // Тайл (зеленый)
        colorCode = "\033[38;5;34m";
        break;
    case 2:
        // Стенка (желтый)
        colorCode = "\033[38;5;226m";
        break;
    case 3:
        // Дверь (красный)
        colorCode = "\033[38;5;196m";
        break;
    case 4:
        colorCode = "\033[38;5;126m";
        break;
    }

    std::cout << colorCode;
}

void environmentRenderer::resetConsoleColor() {
    std::cout << "\033[0m ";  // Сброс цвета
}
