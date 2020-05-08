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
#include <list>

void collisionDetection(std::list<Entity*>& entities, float time, Map map)
{
    std::list<Entity *>::iterator it;

    for (it = entities.begin(); it != entities.end(); it++) {
        {
            if ((*it) -> name != "Player1")
                if (!(*it)->life) {
                    entities.erase(it);
                    break;
                }


            if ((*it)->name == "EasyEnemy")
                (*it)->update(time);

            else (*it)->update(time, map);

            for (auto jt = entities.begin(); jt != entities.end(); jt++) {
                if (!((*it)->life))
                    break;
                if ((*it)->getRect().intersects((*jt) -> getRect())) {

                    (*it)->collision(*jt);
                    (*jt)->collision(*it);
                 }
                }

            }

    }
}


bool Start()
{
    SoundBuffer roarBuffer;
    roarBuffer.loadFromFile("music/Tiger6.wav");
    Sound roar(roarBuffer);

    sf::String map_string[HEIGHT_MAP];

    for (int i=0; i<HEIGHT_MAP; ++i)
        map_string[i] = TileMap[i];

    SoundBuffer screamBuffer;
    screamBuffer.loadFromFile("music/Scream.wav");
    Sound scream(screamBuffer);


    Image easyEnemyImage;
    easyEnemyImage.loadFromFile("images/wolf.png");
    easyEnemyImage.createMaskFromColor(sf::Color::White);

    std::list<Entity*>  entities;
    std::list<Entity*>::iterator it;


    Font font;
    font.loadFromFile("fonts/CyrilicOld.TTF");
    Text text("", font, 100);
    text.setFillColor(Color::Black);

    Image heroImage;

    heroImage.loadFromFile("images/shrek.png");
    heroImage.createMaskFromColor(sf::Color::White);

    Player* p = new Player(heroImage, 750,200, 37, 62, "Player1");
    Enemy* easyEnemy = new Enemy(easyEnemyImage, 50, 680,42,40,"EasyEnemy");
    entities.push_back(easyEnemy);
    entities.push_back(p);


    Clock clock;

    RenderWindow window(sf::VideoMode(640, 480), "Shrek");
    view.reset(sf::FloatRect(0, 0, 640, 480));


    Map* map = new Map(map_string);

    menu(window);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();
        time = time/400;
        if (time > 100)
            time  = 60;


        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            for (it = entities.begin(); it != entities.end();)
            {
                Entity *b = *it;
                { it = entities.erase(it); printf("enemy died in cause of destruction\n");}
                it++;
            }

            delete p;
            delete map;
            return true;
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {

            for (it = entities.begin(); it != entities.end();)
            {
                Entity *b = *it;
                { it = entities.erase(it); printf("enemy died in cause of destruction\n");}
                it++;
            }

            delete p;
            delete map;
            return false;
        }


        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.setView(view);
        window.clear(Color(128,106,89));


        map -> draw(window);
        collisionDetection(entities, time, *map);


//        for (it = entities.begin(); it != entities.end(); it++)
//        {
//            if ((*it)->getRect().intersects(p -> getRect()))
//            {
//                if ((*it)->name == "EasyEnemy"){
//
//                    roar.play();
//
//
//                    std::cout << "(*it)->x" << (*it)->x << "\n";//коорд игрока
//                    std::cout << "p -> x" << p -> x << "\n\n";//коорд врага
//
//                    std::cout << "(*it)->y" << (*it)->y << "\n";//коорд игрока
//                    std::cout << "p -> y" << p -> y << "\n\n";//коорд врага
//                    std::cout << "GROUND " << p -> onGround<< "\n\n";//коорд врага
//
//                    if (abs((p -> x - (*it) -> x)) < 20) {
//                        p -> health -= 25;
//
//                        (*it) -> dx *= -1;
//
//                    }
//
//                    if (abs(p -> y+p -> dy -(*it) -> y) < 100 &&  abs(p -> x+p -> dx -(*it) -> x) < 100 && (!p -> onGround)) {
//                        (*it)->health = 0;
//                        p -> dy = -0.2;
//                    }
//                }
//            }
//        }


        for (it = entities.begin(); it != entities.end(); it++){
            window.draw((*it)->sprite);
        }

        if(!p -> life){

            text.setString("YOU DIED\n");
            text.setPosition(p -> x-200,p -> y-50);
            window.draw(text);
            p -> death(time);
            if (p -> currentFrame > 13)
            {
                window.clear();
                for (it = entities.begin(); it != entities.end();)
                {
                    Entity *b = *it;
                    { it = entities.erase(it); printf("enemy died in cause of destruction\n");}
                    it++;
                }
                delete p;
                delete map;
                return true;       //view.rotate(1.0);
            }
        }

        window.display();


    }

}


void gameRunning()
{
    if (Start())
         gameRunning();
}