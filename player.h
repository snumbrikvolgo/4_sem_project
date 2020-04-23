#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H
#include <SFML/Graphics.hpp>
#pragma once
using namespace sf;

class Player {
private:
    float x, y;
public:
    enum {
        left, right, up, down, jump, stay
    } state;


    float w, h, dx, dy, speed;
    int health;
    bool alive, isSelect, isMove, onGround;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    int playerScore;

    Player(String F, float X, float Y, float W, float H);
    void control();
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);
    float getplayercoordinateX(){
        return x;
    }
    float getplayercoordinateY(){
        return y;
    }
};

#endif //PROJECT_PLAYER_H
