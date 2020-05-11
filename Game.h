#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include <list>
#include "entity.h"
#include "map.h"
#include "player.h"
#include <SFML/Audio.hpp>

#define ENEMY_NUMBER 1


class Game {
public:
    bool life;
    std::list<Entity*> entities;
    Game(Player* p, Map* m);
    void collisionDetection(std::list<Entity*>& entities, float time, Map map);
    int interaction(sf::RenderWindow* window);
    Map* map;
    sf::Text        death_text;


private:

    Player* player;
    float time;
    int enemy_number;
    sf::Clock clock;
    sf::Font        font;
    sf::Text        health_text;

    Image easyEnemyImage;
    SoundBuffer roarBuffer;
    Sound roar;



};

bool Start();
void gameRunning();
//void collisionDetection(std::list<Entity*>& entities, float time, Map map);

#endif //PROJECT_GAME_H
