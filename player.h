#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H
#include <SFML/Graphics.hpp>
#pragma once
#include "map.h"
#include "entity.h"
#include "view.h"

using namespace sf;

class Player : public Entity {
public:
    enum { left, right, up, down, jump, stay } state;//добавляем тип перечисления - состояние объекта
    int playerScore;//эта переменная может быть только у игрока
    Player(Image &image, float X, float Y,int W,int H,String Name);
    void control();
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);
};


#endif //PROJECT_PLAYER_H
