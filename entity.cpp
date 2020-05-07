#include <SFML/Graphics.hpp>
#include "entity.h"
#include <SFML/Audio.hpp>
#include <list>

using namespace sf;

Entity::Entity(Image &image, float X, float Y,int W,int H,String Name){

    x = X;
    y = Y;
    w = W;
    h = H;
    name = Name;
    speed = 0; health = 100; dx = 0; dy = 0;

    life = true; onGround = false; isMove = false;

    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(w / 2, h / 2);
}

FloatRect Entity::getRect(){
    return FloatRect(x, y, w, h);
}

