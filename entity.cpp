#include <SFML/Graphics.hpp>
#include "entity.h"

using namespace sf;

class Entity {
public:
    float dx, dy, x, y, speed,moveTimer;//добавили переменную таймер для будущих целей
    int w,h,health;
    bool life, isMove, onGround;
    Texture texture;
    Sprite sprite;
    String name;//враги могут быть разные, мы не будем делать другой класс для врага.всего лишь различим врагов по имени и дадим каждому свое действие в update в зависимости от имени
    Entity(Image &image, float X, float Y,int W,int H,String Name){
        x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
        speed = 0; health = 100; dx = 0; dy = 0;
        life = true; onGround = false; isMove = false;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w / 2, h / 2);
    }
};
