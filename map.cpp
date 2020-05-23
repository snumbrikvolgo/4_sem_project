#include "map.h"
#include "entity.h"

sf::String TileMap[HEIGHT_MAP] = {
        "000000000000000000000000000000000000000000000000000000000000",
        "0                                                          0",
        "0                                                          0",
        "0    b                                                     0",
        "05555556                                                   0",
        "0                                                          0",
        "0                                                       b  0",
        "0        m                                           4555550",
        "0                                       m                  0",
        "0                                     4556                 0",
        "0                 4556                                     0",
        "0                              s b                         0",
        "0                             45556                        0",
        "0                         m                                0",
        "0                      4556                                0",
        "0                                                          0",
        "0                                                          0",
        "0                                                          0",
        "0                 m2113                                    0",
        "0           211111110003                                   0",
        "0           000000000000                                   0",
        "0  m    b  200000000000013    2113      m      b   m       0",
        "011111111110000000000000001111000001111111111111111111111110",
        "000000000000000000000000000000000000000000000000000000000000"
};

Map::Map(sf::String str[])
{
    tileSize = TILE_SIZE;
    tiledMap = str;
    width = WIDTH_MAP;
    height = HEIGHT_MAP;

    stoneisland.loadFromFile("images/Object/Stone.png");
    stone.setTexture(stoneisland);


    background.loadFromFile("images/BG/BG.png");

    bg.setTexture(background);
    bg.setScale(1.9f,1.0f);

    mushroom.loadFromFile("images/mush.png");
    mush.setTexture(mushroom);

    bushground.loadFromFile("images/Object/Bush (4).png");
    bush.setTexture(bushground);

    map_texture.loadFromFile("images/map3_1.png");
    sprite_.setTexture(map_texture);

}

void Map::draw(sf::RenderWindow &window)
{
    window.draw(bg);
    for(int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
        {
            sprite_.setTextureRect(sf::IntRect(/*i * tileSize_*/ 0, /*j * tileSize_*/ 0, 0, 0));
            sprite_.setPosition(i * tileSize, j * tileSize);

            mush.setTextureRect(sf::IntRect(/*i * tileSize_*/ 0, /*j * tileSize_*/ 0, 0, 0));
            mush.setPosition(i * tileSize, j * tileSize);

            bush.setTextureRect(sf::IntRect(/*i * tileSize_*/ 0, /*j * tileSize_*/ 0, 0, 0));
            bush.setPosition(i * tileSize, j * tileSize);

            stone.setTextureRect(sf::IntRect(/*i * tileSize_*/ 0, /*j * tileSize_*/ 0, 0, 0));
            stone.setPosition(i * tileSize, j * tileSize);

            window.draw(sprite_);
            window.draw(mush);
            window.draw(bush);
            window.draw(stone);

            switch(tiledMap[j][i])
            {
                case 's':
                    stone.setTextureRect(sf::IntRect(0, 0, 90, 54 ));

                case 'b':
                    bush.setTextureRect(sf::IntRect(0, 0, 73, 46));
                case ' ':
                    sprite_.setTextureRect(sf::IntRect(0, 0, 0, 0));
                    break;
                case 'm':
                    mush.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE - 1));
                    break;
                case 'q':
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 2, 0, TILE_SIZE, TILE_SIZE));
                    break;
                case 'r':
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 4, 0, TILE_SIZE, TILE_SIZE));
                    break;
                case 'c':  //wave
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 7, TILE_SIZE, TILE_SIZE, TILE_SIZE));
                    break;
                case 'w':   //water
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 8, TILE_SIZE, TILE_SIZE, TILE_SIZE));
                    break;
                case '6':
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 5, TILE_SIZE, TILE_SIZE, TILE_SIZE));
                    break;
                case '5':
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 4, TILE_SIZE, TILE_SIZE, TILE_SIZE));
                    break;
                case '4':
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 3, TILE_SIZE, TILE_SIZE, TILE_SIZE));
                    break;
                case '0': //boundaries
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 4, 0, TILE_SIZE, TILE_SIZE));
                    break;
                case '1': //top_surface
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 1, 0, TILE_SIZE, TILE_SIZE));
                    break;
                case '2': //top_surface
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 0, 0, TILE_SIZE, TILE_SIZE));
                    break;
                case '3': //top_surface
                    sprite_.setTextureRect(sf::IntRect(TILE_SIZE * 2, 0, TILE_SIZE, TILE_SIZE));
                    break;

                default:
                    break;
            }
            window.draw(mush);
            window.draw(bush);
            window.draw(sprite_);
            window.draw(stone);
        }
}