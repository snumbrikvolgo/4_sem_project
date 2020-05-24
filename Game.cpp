#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <unistd.h>
#include "entity.h"
#include "menu.h"
#include "player.h"
#include "enemy.h"
#include "view.h"
#include "HardEnemy.h"
#include <list>
#include <stdlib.h>
#include "FlyingEnemy.h"

bool Start()
{
    sf::String map_string[HEIGHT_MAP];

    for (int i=0; i<HEIGHT_MAP; ++i)
        map_string[i] = TileMap[i];


    RenderWindow window(sf::VideoMode(640, 480), "Shrek");
    view.reset(sf::FloatRect(0, 0, 640, 480));

    if (!menu(window)) {

        return false;
    }

    Image heroImage;
    heroImage.loadFromFile("images/shrek.png");
    heroImage.createMaskFromColor(sf::Color::White);

    Player* p = new Player(heroImage, 1100,680, 37, 62, "Player1");
    Map* map = new Map(map_string);
    Game* game = new Game(p, map);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.setView(view);
        window.clear(Color(128,106,89));

        if (game -> interaction(&window) == 1) {
            delete p;
            delete map;
            delete game;

            return true;
        }

        map -> draw(window);

        auto it = game->entities.begin();

        for (it = game -> entities.begin(); it != game -> entities.end(); it++){
            window.draw((*it)->sprite);
            window.draw((*it) -> hp -> bar);
        }

        window.draw(game -> health_text);

        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            return true;
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            return false;
        }

        if(!game -> life){
            window.draw(game -> death_text);
        }

        window.display();

    }
}

int Game::mission_manager()
{
    if (mission != 1)
        return 1;
    else if (mission == 1)
    {
        if (player -> stone)
        {
            map -> tiledMap[8][9] = '4';
            map -> tiledMap[8][10] = '5';
            map -> tiledMap[8][11] = '5';
            map -> tiledMap[8][12] = '5';
            map -> tiledMap[8][13] = '5';
            map -> tiledMap[8][14] = '6';
            player -> stone = false;
        }

        if (player -> score == 7)
        {
            if (player -> x < 100 && player -> y < 100) {
                printf("you win\n");
                mission++;
                return 0;
            }
        }
        return 0;
    }
}

Game::Game(Player* p, Map* m)
{
    life = true;
    player = p;
    map = m;
    entities.push_back(player);

    font.loadFromFile("fonts/CyrilicOld.TTF");
    death_text.setFillColor(Color::Black);
    death_text.setFont(font);
    death_text.setString("YOU DIED\n");
    death_text.setCharacterSize(100);

    health_text.setFillColor(Color::Black);
    health_text.setFont(font);
    health_text.setCharacterSize(20);

    mission = 1;

    easy_enemy_number = EASY_ENEMY_NUMBER;
    hard_enemy_number = HARD_ENEMY_NUMBER;
    flying_enemy_number = FLYING_ENEMY_NUMBER;

    easyEnemyImage.loadFromFile("images/wolf.png");
    easyEnemyImage.createMaskFromColor(sf::Color::White);

    flyingEnemyImage.loadFromFile("images/claw.png");
    flyingEnemyImage.createMaskFromColor(sf::Color::White);

    hardEnemyImage.loadFromFile("images/farq.png");
    hardEnemyImage.createMaskFromColor(sf::Color::White);
}

Game::~Game()
{
    map = nullptr;
    entities.clear();

}

void Game::collisionDetection(std::list<Entity *> &entities, float time, Map map)
{
    std::list<Entity *>::iterator it;

    for (it = entities.begin(); it != entities.end(); it++) {
        {
            if ((*it) -> name != "Player1")
                if (!(*it)->life) {
                    entities.erase(it);
                    break;
                }

            if ((*it)->name != "Player1")
            {
                (*it)->update(time);
                (*it) -> hp -> update((*it) -> health, (*it) -> x, (*it) -> y - (*it) -> h);
            }

            else {
                (*it)->update(time, map);
            }

            for (auto jt = entities.begin(); jt != entities.end(); jt++) {
                if (!((*it)->life))
                    break;

                FloatRect opp_rect = (*jt) -> getRect();
                FloatRect cur_rect = (*it)->getRect();

                if (opp_rect != cur_rect) {
                    if ((*it) -> name == "HardEnemy") (*it) -> shrek_near(*jt);
                    if ((*it) -> name == "Raven") (*it) -> shrek_near(*jt);
                    if (cur_rect.intersects(opp_rect)) {

                        (*it)->collision(*jt);
                        (*jt)->collision(*it);
                    }
                }
            }

        }

    }
}

int Game::interaction(sf::RenderWindow* window)
{
    time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time /= 400;
    if (time > 100)
        time = 70;

    if (mission_manager())
        return 1;
    if (easy_enemy_number)
    {
        for (int i = 0; i < easy_enemy_number; i++) {
            entities.push_back(new Enemy(easyEnemyImage, 50, 680,42,40,"EasyEnemy"));
        }

        easy_enemy_number = 0;
    }

    if (hard_enemy_number)
    {
        for (int i = 0; i < hard_enemy_number; i++) {
            entities.push_back(new HardEnemy(hardEnemyImage, 1500, 680,42,40,"HardEnemy"));
        }

        hard_enemy_number = 0;
    }

    if (flying_enemy_number)
    {
        for (int i = 0; i < flying_enemy_number; i++) {
            entities.push_back(new Raven(flyingEnemyImage, 1000, 200,35,60,"Raven"));
        }

        flying_enemy_number = 0;
    }

    if (!player -> life)
    {
        life = false;
        death_text.setPosition(player -> x - 200, player -> y - 50);
        player -> death(time);
            if (player -> currentFrame > 13)
            {
                window -> clear();
                return 1;
            }

    }
    collisionDetection(entities, time, *map);

    std::ostringstream health;
    health << player -> health << " Mushs: ";
    health_text.setString("Health:" + health.str() + std::to_string(player -> score) + " " + "/7");
    health_text.setPosition(sf::Vector2f(view.getCenter().x-300, view.getCenter().y - 230));

    return 0;

}
void gameRunning()
{
    if (Start())
         gameRunning();
}