#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "player.h"
#include "mission.h"
#include "map.h"
#include "view.h"

using namespace sf;

int main()
{
    bool showMissionText = true;
    int createObjectForMapTimer = 0;

    Image quest_image;
    quest_image.loadFromFile("images/scroll.jpg");
    quest_image.createMaskFromColor(Color(0, 0, 0));
    Texture quest_texture;
    quest_texture.loadFromImage(quest_image);
    Sprite s_quest;
    s_quest.setTexture(quest_texture);
    s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
    s_quest.setScale(0.6f, 0.6f);//чуть уменьшили картинку, => размер стал меньше

    Font font;//шрифт
    font.loadFromFile("fonts/CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
    Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setFillColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый

    float CurrentFrame=0;
    Player p("shrek.png", 150,150, 37, 62);
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
    Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры
    int gameTime = 0;//объявили игровое время, инициализировали.

    RenderWindow window(sf::VideoMode(1366, 768), "Shrek");
    view.reset(sf::FloatRect(0, 0, 640, 480));

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)//событие нажатия клавиши
                if ((event.key.code == Keyboard::Tab)) {
                    switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText
                        case true: {
                            std::ostringstream playerHealthString;//строка здоровья игрока
                            playerHealthString << p.health; //заносим в строку здоровье
                            std::ostringstream task;//строка текста миссии
                            task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
                            text.setString(L"Здоровье: " + playerHealthString.str()+"\n" + task.str());//задаем
                            //text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
                            //s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока
                            showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране
                            break;//выходим , чтобы не выполнить условие "false" (которое ниже)
                        }
                        case false: {
                            text.setString("");//если не нажата клавиша таб, то весь этот текст пустой
                            showMissionText = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
                            break;
                        }
                    }
                }
        }


            gameTime=gameTimeClock.getElapsedTime().asSeconds();
            clock.restart(); //перезагружает время
            time = time/400;


        p.update(time);

        window.setView(view);
        window.clear(Color(128,106,89));

        if ((getCurrentMission(p.getplayercoordinateX())) == 0) { //Если текущая миссия 0, то рисуем карту вот так
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
        }
        if ((getCurrentMission(p.getplayercoordinateX())) >= 1) { //Если текущая миссия 1, то рисуем карту вот так
            for (int i = 0; i < HEIGHT_MAP; i++)
                for (int j = 0; j < WIDTH_MAP; j++)
                {
                    if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 0, 32, 32));//для примера поменял местами вывод спрайта для этого символа и..
                    if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
                    if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//и для вот этого. логически-игровой смысл их остался таким же
                    if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
                    if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
                    s_map.setPosition(j * 32, i * 32);
                    window.draw(s_map);
                }
        }

        createObjectForMapTimer += time;//наращиваем таймер
        if (createObjectForMapTimer>3000){
            randomMapGenerate();//генерация случ камней
            createObjectForMapTimer = 0;//обнуляем таймер
        }

        //window.draw(background);
        std::ostringstream playerHealthString,gameTimeString;    // объявили переменную здоровья и времени
        playerHealthString << p.health; gameTimeString << gameTime;		//формируем строку
        //text.setString(L"Здоровье: " + playerHealthString.str()+L"\nВремя игры: "+gameTimeString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()

        //text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
        if (!showMissionText) {
            text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
            s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока
            window.draw(s_quest); window.draw(text); //рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
        }

        window.draw(p.sprite);
        window.display();
    }

    return 0;
}
