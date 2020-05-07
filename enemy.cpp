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
    //std::cout << "Enemy created" << " " << x << " " << " " << y << " " << " "<< w << h  << std::endl;
    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
    float next_position_x = x + dx;
    int j = next_position_x / 32;
    int i = (y)/32;

    if (TileMap[i][j] == ' ') {
        printf("wolf in the air\n");

        dy = 0.2;
        y = i * 32;
    }

    if (TileMap[i][j] == '1' || TileMap[i][j] == '2' ||
        TileMap[i][j] == '3' || TileMap[i][j] == '4' || TileMap[i][j] == '5'
        || TileMap[i][j] == '6')

    {
        dx *= -1;
    }

    if (TileMap[i][j] == '0')
    {
        dx *= -1;
//            if (Dy > 0) {
//                y = i * 32 - h - 100;
//                dy = 0;
//                onGround = true;
//            }

//                if (Dx>0)
//                { x = j * 32 - w; }
//                if (Dx<0)
//                { x = j * 32 + 32; }

    }

    if (TileMap[i][j] == 'w' || TileMap[i][j] == 'c')
    {
        speed = 0;
        onGround = false;
        health = 0;
    }
}

void Enemy::control(float time)
{
    if (dx < 0) {
        currentFrame += 0.005 * time;
        if (currentFrame > 3) currentFrame -= 3;
        sprite.setTextureRect(IntRect(42 * int(currentFrame), 0, 42, 40));
        sprite.move(0, 0.1 * time);
        sprite.setScale(-1.0f, 1.0f);
    }

    if (dx > 0) {
        currentFrame += 0.005 * time;
        if (currentFrame > 3) currentFrame -= 3;
        sprite.setTextureRect(IntRect(42 * int(currentFrame), 0, 42, 40));
        sprite.move(0.1 * time, 0);
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

        checkCollisionWithMap(0, dy);


        sprite.setPosition(x + w/2 , y + h / 2);

        if (health <= 0){
            dx = 0;
            dy = 0;
            speed = 0;
            life = false; }
    }
}

void Enemy::update(float time, Map map){};

void Enemy::collision(Entity* enemy)
{
    if (enemy -> name == "EasyEnemy")
        dx *= -1;
    else if (enemy -> name == "Player1")
    {
        dx *= -1;
        if (abs(y - enemy->y) < 50 && abs(x + dx - enemy -> x) < 70 &&
            !(enemy -> onGround)) {

                        health = 0;
        }
    }
}