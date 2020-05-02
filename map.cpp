//
// Created by snumbrikvolgo on 23.04.20.
//
#include "map.h"
sf::String TileMap[HEIGHT_MAP] = {
        "0000000000000000000000000000000000000000",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0              s    0000               0",
        "0           000000000000               0",
        "0           000000000000               0",
        "0   f    h  000000000000               0",
        "0000000000000000000000000000000000000000",
};

void randomMapGenerate(){//рандомно расставляем камни
    int randomElementX = 0;//случайный элемент по горизонтали
    int randomElementY = 0;//случ эл-т по вертикали
    srand(time(0));//рандом
    int countStone = 2;//количество камней
    while (countStone>0){
        randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
        randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же
        if (TileMap[randomElementY][randomElementX] == ' ')   {//если встретили символ пробел,
            TileMap[randomElementY][randomElementX] = 's'; //то ставим туда камень.
            //std::cout << "coordinate of Stone X:" << randomElementX << "\n" << "coordinate of Stone Y:" << randomElementY << "\n\n";
            countStone--;
        }
    }
}
