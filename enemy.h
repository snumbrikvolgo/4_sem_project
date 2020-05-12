//
// Created by snumbrikvolgo on 02.05.20.
//

#ifndef PROJECT_ENEMY_H
#define PROJECT_ENEMY_H

#include "entity.h"
#include <SFML/Audio.hpp>

class Enemy :public Entity{
public:
    Enemy(Image &image, float X, float Y,int W,int H,String Name);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);
    void update(float time, Map map){};
    void collision(Entity* enemy);

    void control(float time);
    float moveTimer;
    bool shrek_near(Entity* shrek){};

    sf::SoundBuffer roarBuffer;
    sf::Sound roar;
};

#endif //PROJECT_ENEMY_H
