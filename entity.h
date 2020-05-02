#ifndef PROJECT_ENTITY_H
#define PROJECT_ENTITY_H
#pragma once


#include <SFML/Graphics.hpp>
using namespace sf;
class Entity {
public:
    float dx, dy, x, y, speed,moveTimer;
    int w,h,health;
    bool life, isMove, onGround;
    Texture texture;
    Sprite sprite;
    String name;

    Entity(Image &image, float X, float Y,int W,int H,String Name);
    virtual void update(float time) = 0;
};
#endif //PROJECT_ENTITY_H
