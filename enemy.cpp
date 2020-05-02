#include "enemy.h"
#include "map.h"
#include <iostream>

Enemy::Enemy(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name){
    if (name == "EasyEnemy"){
    sprite.setTextureRect(IntRect(0, 0, w, h));
    dx = 0.1;//даем скорость.этот объект всегда двигается
    moveTimer = 0;

    //std::cout << "Enemy created" << " " << x << " " << " " << y << " " << " "<< w << h  << std::endl;
    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
    for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j<(x + w) / 32; j++)
        {
            if (TileMap[i][j] == '0')
            {
                if (Dy>0){ y = i * 32 - h; }
                if (Dy<0){ y = i * 32 + 32; }
                if (Dx>0){ x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }
                if (Dx<0){ x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }
            }
        }
}

void Enemy::update(float time)
{
    if (name == "EasyEnemy"){
        moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
        checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
        //x += dx*time;
        sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
        //std::cout << "position" << "x+w/2" << x+w/2 << std::endl;
        if (health <= 0){ life = false; }
    }
}