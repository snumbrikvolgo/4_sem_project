#include "player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

Player::Player(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name){
    playerScore = 0; state = stay;
    if (name == "Player1"){
        sprite.setTextureRect(IntRect(43, 0, w, h));
    }
    //std::cout << "/player created" << " " << x << " " << " " << y << " " << " "<< w << h  << std::endl;
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
            for (int j = x / 32; j<(x + w) / 32; j++)
            {
                if (TileMap[i][j] == '0')//если элемент наш тайлик земли? то
                {
                    if (Dy>0){ y = i * 32 - h;  dy = 0; onGround = true; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
                    if (Dy<0){ y = i * 32 + 32;  dy = 0; }//столкновение с верхними краями карты(может и не пригодиться)
                    if (Dx>0){ x = j * 32 - w; }//с правым краем карты
                    if (Dx<0){ x = j * 32 + 32; }// с левым краем карты
                }
//else { onGround = false; }//надо убрать т.к мы можем находиться и на другой поверхности или платформе которую разрушит враг
            }
    }
void Player::update(float time) {
    control();//функция управления персонажем
    std::cout << "state " << state << std::endl;
    switch (state)//тут делаются различные действия в зависимости от состояния
    {
        case right:dx = speed; break;//состояние идти вправо
        case left:dx = speed; break;//состояние идти влево
        case up: break;//будет состояние поднятия наверх (например по лестнице)
        case down: dx = 0; break;//будет состояние во время спуска персонажа (например по лестнице)
        case stay: break;//и здесь тоже
    }
    x += dx*time;
    checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
    y += dy*time;
    checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
    sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
    if (health <= 0){ life = false; }
    if (!isMove){ speed = 0; }
//if (!onGround) { dy = dy + 0.0015*time; }//убираем и будем всегда притягивать к земле
    if (life) { setPlayerCoordinateForView(x, y); }
    dy = dy + 0.0015*time;//постоянно притягиваемся к земле
}
