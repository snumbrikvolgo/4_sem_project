#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H
#include <SFML/Graphics.hpp>
#pragma once

using namespace sf;

const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 60;
const int TILE_SIZE = 32;


extern sf::String TileMap[HEIGHT_MAP];
extern sf::String CopyTileMap[HEIGHT_MAP];

class Map {
public:

    Map(sf::String str[]);
    void draw (sf::RenderWindow &window);

    int getWidth()  { return width;};
    int getHeight() { return height;};

    sf::String *  tiledMap;

private:
    int width;
    int height;

    Texture map_texture;
    Sprite sprite_;

    Texture background;
    Sprite bg;

    Texture bushground;
    Sprite bush;

    Texture stoneisland;
    Sprite stone;

    Texture mushroom;
    Sprite mush;

    int                 tileSize;
};

#endif //PROJECT_MAP_H
