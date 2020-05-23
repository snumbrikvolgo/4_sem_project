//
// Created by snumbrikvolgo on 14.05.20.
//

#ifndef PROJECT_FLYINGENEMY_H
#define PROJECT_FLYINGENEMY_H

#include "entity.h"

class Raven :public Entity{
public:
    Raven(Image &image, float X, float Y,int W,int H,String Name);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);
    void update(float time, Map map){};
    void collision(Entity* enemy);
    float shrek_x;
    float shrek_y;

    void control(float time);
    float moveTimer;
    float nearTimer;
    bool ro_dah;

    bool shrek_near(Entity* shrek);
    bool is_near;
};

#endif //PROJECT_FLYINGENEMY_H
