#include "mapRenderer.h"
#include <iostream>

    char MapRenderer::getSymbolForCellValue(int cellValue) {
        switch (cellValue) {
        default:
            return ' ';  // По умолчанию, например, для неизвестных значений
        case 0:
            return ' ';  // Решетка
        case 1:
            return '.';  // Тайл
        case 2:
            return 'I';  // Стенка
        case 3:
            return 'H';  // Дверь
        case 4:
            return 'H'; // Дверь
        case 5:
            return 'V'; // Облако дыма
        case 6:
            return 'M'; // Магмовый камень
        case 7:
            return 'A'; // Пепел и каменные осколки
        case 8:
            return 'F'; // Огонь 
        case 10:
            return 'I'; // угловой 
        case 11:
            return 'I'; // горизонтальный
        case 12:
            return 'I'; // вертикальный 
        case 13:
            return 'I'; // вертикальный 
        case 14:
            return 'I'; // вертикальный 
        case 15:
            return 'Y';
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
            // Дверь 
            colorCode = "\033[38;5;196m";
            break;
        case 4:
            // Дверь
            colorCode = "\033[38;5;200m";
            break;
        case 10:
            // Стена
            colorCode = "\033[38;5;110m";
            break;
        case 11:
            // Стена
            colorCode = "\033[38;5;120m";
            break;
        case 12:
            // Стена
            colorCode = "\033[38;5;120m";
            break;
        case 13:
            // Стена
            colorCode = "\033[38;5;130m";
            break;
        case 14:
            // Стена
            colorCode = "\033[38;5;130m";
            break;
        case 15:
            // грибы
            colorCode = "\033[38;5;12m";
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
