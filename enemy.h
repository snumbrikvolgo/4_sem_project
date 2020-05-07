//
// Created by snumbrikvolgo on 02.05.20.
//

#ifndef PROJECT_ENEMY_H
#define PROJECT_ENEMY_H

#include "entity.h"

class Enemy :public Entity{
public:
    Enemy(Image &image, float X, float Y,int W,int H,String Name);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);

    void control(float time);
    float moveTimer;
};

#endif //PROJECT_ENEMY_H
