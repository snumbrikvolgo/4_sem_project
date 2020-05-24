#include "enemy.h"
#include "map.h"
#include <iostream>

Enemy::Enemy(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name)
{
    if (name == "EasyEnemy"){
        sprite.setTextureRect(IntRect(0, 0, w, h));
        dx = 0.025;
        moveTimer = 0;
        onGround = false;
    }

    roarBuffer.loadFromFile("music/Tiger6.wav");
    roar.setBuffer(roarBuffer);

}
Enemy::~Enemy()
{}

void Enemy::collision(Entity* enemy){
    if (enemy -> name == "EasyEnemy" || enemy -> name == "HardEnemy" || enemy -> name == "Raven")
    {
        if (dx * (enemy -> dx) > 0)
        {
            dx *= -1;
        }
        else {
            if (dx > 0)
                x -= w / 2;
            else x += w / 2;
        }
    }
    else if (enemy -> name == "Player1")
    {
        roar.play();
        if (dx > 0)
            x -= w/2;
        else x +=w/2;

        if ((y - enemy->y) < 100 && abs(x - enemy -> x) < (enemy -> w + w)/2 &&
            !(enemy -> onGround)) {
            health -= 5;
        }
    }
}
void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
    float next_position_x = x + Dx;
    int j = next_position_x / 32;
    int i = (y)/32;

    if (TileMap[i][j] == ' ') {
        dy = 0.2;
        y = i * 32;
    }

    else if (TileMap[i][j] == '1' || TileMap[i][j] == '2' ||
        TileMap[i][j] == '3' || TileMap[i][j] == '4' || TileMap[i][j] == '5'
        || TileMap[i][j] == '6' || TileMap[i][j] == '0')
    {
        if (TileMap[i][j -1] == ' ')
        {
            //printf("left free\n");
            x = j*32 - 64;
        }
        else if(TileMap[i][j + 1] == ' ')
        {
            //printf("right free\n");
            x = j*32 + 64;
        }
        dx *= -1;
    }

    else if (TileMap[i][j] == 'w' || TileMap[i][j] == 'c')
    {
        speed = 0;
        onGround = false;
        health = 0;
    }
}

void Enemy::control(float time)
{
    if (dx < 0) {
        sprite.move(0, 0.1 * time);
        play_animation(3, 0, 40, 42, 0, 1, time);
        sprite.setScale(-1.0f, 1.0f);
    }

    if (dx > 0) {
        sprite.move(0.1 * time, 0);
        play_animation(3, 0, 40, 42, 0, 1, time);
        sprite.setScale(1.0f, 1.0f);
    }

}

void Enemy::update(float time)
{
    if (name == "EasyEnemy"){
        control(time);
        moveTimer += time;

        if (moveTimer > 8000)
        {
            dx *= -1;
            moveTimer = 0;
        }

        checkCollisionWithMap(dx, 0);
        x += dx*time;
        sprite.setPosition(x + w/2 , y + h / 2);

        if (health <= 0)
        {
            dx = 0;
            dy = 0;
            speed = 0;
            life = false;
        }
    }

}