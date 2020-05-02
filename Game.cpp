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


bool Start()
{
    SoundBuffer shootBuffer;//создаём буфер для звука
    shootBuffer.loadFromFile("music/drive.wav");//загружаем в него звук
    Sound shoot(shootBuffer);//создаем звук и загружаем в него звук из буфера

    Music music;//создаем объект музыки
    music.openFromFile("music/shrek.ogg");//загружаем файл
    //music.play();//воспроизводим музыку

    Image easyEnemyImage;
    easyEnemyImage.loadFromFile("images/shamaich.png");
    easyEnemyImage.createMaskFromColor(Color(255, 0, 0));

    std::list<Entity*>  entities;//создаю список, сюда буду кидать объекты.например врагов.
    std::list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка

    Font font;
    font.loadFromFile("fonts/CyrilicOld.TTF");
    Text text("", font, 100);
    text.setFillColor(Color::Black);

    Image heroImage;

    heroImage.loadFromFile("images/shrek.png");
    heroImage.createMaskFromColor(
            sf::Color::White);

    Player p(heroImage, 750,200, 37, 62, "Player1");
    Enemy easyEnemy(easyEnemyImage, 64, 600,200,97,"EasyEnemy");//простой враг, объект класса врага
    entities.push_back(&easyEnemy);


    Clock clock;
    Clock gameTimeClock;

    RenderWindow window(sf::VideoMode(640, 480), "Shrek");
    view.reset(sf::FloatRect(0, 0, 640, 480));

    Map map_grand;
    menu(window);//вызов меню

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds();

        if (Keyboard::isKeyPressed(Keyboard::Tab))    { return true; }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        clock.restart();
        time = time/400;

        p.update(time);

        for (it = entities.begin(); it != entities.end(); it++) { (*it)->update(time);}

        window.setView(view);
        window.clear(Color(128,106,89));


        map_grand.draw(window);


        for (it = entities.begin(); it != entities.end(); it++)//проходимся по эл-там списка
        {
            if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
            {
                if ((*it)->name == "EasyEnemy"){//и при этом имя объекта EasyEnemy,то..
                    shoot.play();
                    if ((*it)->dx>0)//если враг идет вправо
                    {
                        std::cout << "(*it)->x" << (*it)->x << "\n";//коорд игрока
                        std::cout << "p.x" << p.x << "\n\n";//коорд врага
                        (*it)->x = p.x - (*it)->w; //отталкиваем его от игрока влево (впритык)
                        (*it)->dx = -1;//останавливаем
                        std::cout << "new (*it)->x" << (*it)->x << "\n";//новая коорд врага
                        std::cout << "new p.x" << p.x << "\n\n";//новая коорд игрока (останется прежней)
                    }
                    if ((*it)->dx < 0)//если враг идет влево
                    {
                        (*it)->x = p.x + p.w; //аналогично - отталкиваем вправо
                        (*it)->dx = 1;//останавливаем
                    }
                }
            }
        }

        for (it = entities.begin(); it != entities.end();)//говорим что проходимся от начала до конца
        {
            Entity *b = *it;//для удобства, чтобы не писать (*it)->
            b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
            if (b->life == false)	{ it = entities.erase(it); }// если этот объект мертв, то удаляем его
            else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
        }



        for (it = entities.begin(); it != entities.end(); it++){
            window.draw((*it)->sprite);
        }

        window.draw(p.sprite);
        window.display();

        if(!p.life){
            text.setString("YOU DIED\n");
            text.setPosition(p.x+50,p.y+50);
            window.draw(text);
            p.death(time);

            if (p.currentFrame > 13)
            {
                window.clear();

                return true;       //view.rotate(1.0);
            }
        }
    }
}


void gameRunning()
{
    if (Start())
         gameRunning();
}