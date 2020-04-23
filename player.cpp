#include "player.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"

using namespace sf;

    Player::Player(String F, float X, float Y, float W, float H) {
        state = stay;
        speed = 0; playerScore = 0;
        health = 100;
        isMove = false;
        onGround = false;
        alive = true;
        x = 0;
        y = 0;
        dx = 0;
        dy = 0;
        File = F;
        w = W;
        h = H;
        image.loadFromFile("images/" +
                           File);
        image.createMaskFromColor(
                sf::Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X;
        y = Y;
        sprite.setTextureRect(IntRect(43, 0, w,
                                      h));
        sprite.setOrigin(w/2, h/2);
    }
    void Player::control() {
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            state = left;
            speed = -0.1;
//currentFrame += 0.005*time;
//if (currentFrame > 3) currentFrame -= 3;
//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 135, 96, 54));
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            state = right;
            speed = 0.1;
//            p.dir = 0;
//            p.speed = 0.1;//направление вправо, см выше
//            CurrentFrame += 0.005 * time;
//            if (CurrentFrame > 4) CurrentFrame -= 4; // если пришли к третьему кадру - откидываемся назад.
//            p.sprite.setTextureRect(IntRect(43 * int(CurrentFrame) + 79, 68, 43,
//                                            50)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
//            p.sprite.move(0.1 * time, 0);//происходит само движение персонажа влево
//            p.sprite.setScale(1.0f, 1.0f);
        }
        if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
            state = jump;
            dy = -0.5;
            onGround = false;//то состояние равно прыжок,прыгнули и сообщили, что мы не на земле
            //  p.dir = 3;
//                p.speed = 0.1;//направление вниз, см выше
//                CurrentFrame += 0.005 * time;
//                if (CurrentFrame > 4) CurrentFrame -= 4; // если пришли к третьему кадру - откидываемся назад.
//                p.sprite.setTextureRect(IntRect(36 * int(CurrentFrame) + 98, 130, 36,
//                                                50)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
//                p.sprite.move(0, -0.1 * time);//происходит само движение персонажа влево
//                p.sprite.setScale(1.0f, 1.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            state = down;
            speed = 0.1;
//            p.dir = 2;
//            p.speed = 0.1;//направление вверх, см выше
//            CurrentFrame += 0.005 * time;
//            p.sprite.move(0, 0.1 * time);
//            p.sprite.setTextureRect(IntRect(195, 250, 37, 42));
        }
    }
    void Player::checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
    {
        for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
            for (int j = x / 32; j<(x + w) / 32; j++) {
                if (TileMap[i][j] == '0')//если элемент наш тайлик земли? то
                {
                    if (Dy > 0) {
                        y = i * 32 - h;
                        dy = 0;
                        onGround = true;
                    }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
                    if (Dy < 0) {
                        y = i * 32 + 32;
                        dy = 0;
                    }//столкновение с верхними краями карты(может и не пригодиться)
                    if (Dx > 0) { x = j * 32 - w; }//с правым краем карты
                    if (Dx < 0) { x = j * 32 + 32; }// с левым краем карты
                } else { onGround = false; }


                if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
                    playerScore++;
                    TileMap[i][j] = ' ';
                }
                if (TileMap[i][j] == 'f') {
                    health -= 40;//если взяли ядовитейший в мире цветок,то переменная health=health-40;
                    TileMap[i][j] = ' ';//убрали цветок
                }
                if (TileMap[i][j] == 'h') {
                    health += 20;//если взяли сердечко,то переменная health=health+20;
                    TileMap[i][j] = ' ';//убрали сердечко
                }
            }
    }
    void Player::update(float time) {
        control();//функция управления персонажем
        switch (state)//тут делаются различные действия в зависимости от состояния
        {
            case right: dx = speed;break;//состояние идти вправо
            case left: dx = speed;break;//состояние идти влево
            case up: break;//будет состояние поднятия наверх (например по лестнице)
            case down: dx=0;break;//будет состояние во время спуска персонажа (например по лестнице)
            case jump: break;//здесь может быть вызов анимации
            case stay: break;//и здесь тоже
        }
        x += dx*time;
        checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
        y += dy*time;
        checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
        if (!isMove) speed = 0;
        sprite.setPosition(x+w/2, y+h/2); //задаем позицию спрайта в место его центра
        if (health <= 0){alive = false; speed  = 0;}
        dy = dy + 0.0015*time;

        if (alive) {
            getplayercoordinateforview(getplayercoordinateX(), getplayercoordinateY());

        }

    }
