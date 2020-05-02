#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "view.h"
#include <list>
#include "mission.h"
sf::View view;

using namespace sf;

int main()
{
    bool showMissionText = true;
    int createObjectForMapTimer = 0;

    Image easyEnemyImage;
    easyEnemyImage.loadFromFile("images/shamaich.png");
    easyEnemyImage.createMaskFromColor(Color(255, 0, 0));

    std::list<Entity*>  entities;//создаю список, сюда буду кидать объекты.например врагов.
    std::list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка

    Font font;
    font.loadFromFile("fonts/CyrilicOld.TTF");
    Text text("", font, 20);
    text.setFillColor(Color::Black);

    Image heroImage;

    heroImage.loadFromFile("images/shrek.png");
    heroImage.createMaskFromColor(
            sf::Color::White);

    float CurrentFrame=0;
    Player p(heroImage, 750,500, 37, 62, "Player1");
    Enemy easyEnemy(easyEnemyImage, 750, 600,200,97,"EasyEnemy");//простой враг, объект класса врага
    entities.push_back(&easyEnemy);


    Texture bg;
    bg.loadFromFile("images/BG/BG.png");
    Sprite background(bg);


    Image map_image;//объект изображения для карты
    map_image.loadFromFile("images/map 2.png");//загружаем файл для карты
    Texture map;//текстура карты
    map.loadFromImage(map_image);//заряжаем текстуру картинкой
    Sprite s_map;//создаём спрайт для карты
    s_map.setTexture(map);//заливаем текстуру спрайтом

    Clock clock;
    Clock gameTimeClock;
    int gameTime = 0;

    RenderWindow window(sf::VideoMode(640, 480), "Shrek");
    view.reset(sf::FloatRect(0, 0, 640, 480));

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Escape)
                    window.close();
        }

            gameTime=gameTimeClock.getElapsedTime().asSeconds();
            clock.restart();
            time = time/400;


        p.update(time);
        for (it = entities.begin(); it != entities.end(); it++) { (*it)->update(time);}//для всех элементов списка(пока это только враги,но могут быть и пули к примеру) активируем ф-цию update
        //easyEnemy.update(time);

        window.setView(view);
        window.clear(Color(128,106,89));

        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
                if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
                if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
                if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
                if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }
        //window.draw(background);

        window.draw(easyEnemy.sprite);
        window.draw(p.sprite);
        window.display();
    }

    return 0;
}
