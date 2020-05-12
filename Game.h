#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include <list>
#include "entity.h"
#include "map.h"
#include "player.h"
#include <SFML/Audio.hpp>

#define EASY_ENEMY_NUMBER 1
#define HARD_ENEMY_NUMBER 1

class Game {
public:
    bool life;
    std::list<Entity*> entities;
    Game(Player* p, Map* m);
    void collisionDetection(std::list<Entity*>& entities, float time, Map map);
    int interaction(sf::RenderWindow* window);
    int mission_manager();
    Map* map;
    sf::Text        death_text;
    sf::Text        health_text;

    int mission;
private:

    Player* player;
    float time;

    int easy_enemy_number;
    int hard_enemy_number;

    sf::Clock clock;
    sf::Font        font;


    Image easyEnemyImage;
    Image hardEnemyImage;





};

bool Start();
void gameRunning();

#endif //PROJECT_GAME_H
