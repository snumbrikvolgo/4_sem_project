#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#pragma once
#include "map.h"
#include "entity.h"
#include "view.h"

using namespace sf;

class Player : public Entity {
public:
    enum { left, right, up, down, jump, stay } state;


    Player(Image &image, float X, float Y,int W,int H,String Name);

    int score;
    bool stone;

    void control(float time);
    void checkCollisionWithMap(float Dx, float Dy, Map m);
    void update(float time, Map m);
    void update(float time);
    void death(float time);
    void collision(Entity* enemy);
    bool shrek_near(Entity* shrek){};

    sf::SoundBuffer screamBuffer;
    sf::Sound scream;
};


#endif //PROJECT_PLAYER_H
