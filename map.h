#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H
#include <SFML/Graphics.hpp>
#pragma once

const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 40;//размер карты ширина


extern sf::String TileMap[HEIGHT_MAP];

void randomMapGenerate();


#endif //PROJECT_MAP_H
