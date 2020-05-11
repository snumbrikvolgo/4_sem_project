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

    else if (name == "HardEnemy")
    {
        printf("creating\n");
        sprite.setTextureRect(IntRect(0, 0, 33, 47));
        dx = 0;
        moveTimer = 0;
        onGround = false;
        //sprite.setScale(2.0f, 2.0f);
    }

}
void Enemy::collision(Entity* enemy){
    if (enemy -> name == "EasyEnemy" || enemy -> name == "HardEnemy")
        dx *= -1;

    else if (enemy -> name == "Player1")
    {
        dx *= -1;
        if (abs(y - enemy->y) < 100 && abs(x - enemy -> x) < 70 &&
            !(enemy -> onGround)) {

            health = 0;
        }
    }
}
void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
//    printf("Enemy x %f\n" ,x);
//    printf("Enemy y %f\n" ,y);

    float next_position_x = x + dx;
    int j = next_position_x / 32;
    int i = (y)/32;

    if (TileMap[i][j] == ' ') {
        //printf("wolf in the air\n");

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
//                //printf("hhuii\n");
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

        checkCollisionWithMap(0, dy);


        sprite.setPosition(x + w/2 , y + h / 2);

        if (health <= 0)
        {
            dx = 0;
            dy = 0;
            speed = 0;
            life = false;
        }
    }
    else if (name == "HardEnemy")
    {
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


        sprite.setPosition(x  + w/3, y + h/4);

        if (health <= 0)
        {
            dx = 0;
            dy = 0;
            speed = 0;
            life = false;
        }

    }
}