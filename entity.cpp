#include <SFML/Graphics.hpp>
#include "entity.h"

using namespace sf;
bool Entity::shrek_near(Entity* shrek){}

Entity::Entity(Image &image, float X, float Y,int W,int H,String Name)
{

    currentFrame = 0;
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
    hp = new Health(100);
}
Entity::~Entity()
{
    life = false;
    texture.~Texture();
    sprite.~Sprite();
}

FloatRect Entity::getRect(){
    return {x, y, (float)w, (float)h};
}

void Entity::play_animation(int num, int shift, int height, int width, int down, int cycle, float time){
    currentFrame += 0.005 * time;
    if (cycle)
    {
        if (currentFrame > num) currentFrame -= num;

    }
    sprite.setTextureRect(IntRect(width * int(currentFrame) + shift, down , width, height));
}