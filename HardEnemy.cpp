#include "HardEnemy.h"
#include "enemy.h"
#include "map.h"
#include <iostream>
#include <math.h>

HardEnemy::HardEnemy(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name)
{
   if (name == "HardEnemy")
    {
        sprite.setTextureRect(IntRect(0, 0, 33, 47));
        dx = 0;
        moveTimer = 0;
        onGround = false;
        is_near = true;
        visible = false;

        start_x = X;
        start_y = Y;
    }

}
void HardEnemy::collision(Entity* enemy)
{
    if (enemy -> name == "EasyEnemy" || enemy -> name == "HardEnemy" || enemy -> name == "Raven")
    {
        if (dx * (enemy -> dx) > 0)
        {
            //dx = 0;
        }
        else {
            if (dx > 0)
                x -= w / 2;
            else x += w / 2;
        }
    }
    else if (enemy -> name == "Player1")
    {
        if (dx > 0)
            x -= w/2;
        else x +=w/2;

        if (abs(y - enemy->y) < 100 && abs(x - enemy -> x) < 70 &&
            !(enemy -> onGround)) {

            health -= 20;
        }
    }
}
void HardEnemy::checkCollisionWithMap(float Dx, float Dy)
{
    float next_position_x = x + dx;
    int j = next_position_x / 32;
    int i = (y)/32;

    if (TileMap[i][j] =='0' && TileMap[i-1][j] == '0')
    {
        //printf("near double 0\n");
        dx *= -1;
        dy = 0.2;
        y = i * 32 - 32;
    }

    else if (TileMap[i][j] == ' ' && TileMap[i+1][j] == ' ')
    {
        //printf("near empty\n");
        y = i * 32 + 32;
        dy = 0.2;
    }

    else if (TileMap[i][j] == ' ' || TileMap[i][j] == 'm')
    {

        if (Dy < 0)
        {
            y = i * 32 + 32;  dy = 0.2;
        }
        else {
            dy = 0.2;
            y = i * 32;
        }

    }
    else if (TileMap[i][j] == 'b')
    {

        dy = 0.2;
        y = i * 32;
    }

    else if (TileMap[i][j] == '1' || TileMap[i][j] == '2' ||
        TileMap[i][j] == '3' || TileMap[i][j] == '4' || TileMap[i][j] == '5'
        || TileMap[i][j] == '6'||TileMap[i][j] == '0')

    {
        //printf("next ground\n");
        dy = 0.2;
        y = i * 32 - 32;
    }

    else if (TileMap[i][j] == '0')
    {
        dx *= -1;
        dy = 0.2;

    }

}

void HardEnemy::control(float time)
{
    if (dx < 0) {
        sprite.move(0.1 * time, 0);
        play_animation(3, 0, 48, 33, 0, 1, time);
        sprite.setScale(-1.0f, 1.0f);
    }

    if (dx > 0) {
        sprite.move(0.1 * time, 0);
        play_animation(3, 0, 48, 33, 0, 1, time);
        sprite.setScale(1.0f, 1.0f);
    }

}

void HardEnemy::update(float time)
{
  if (name == "HardEnemy")
    {
        if (abs (x - start_x) < 10 && !is_near)
        {
            sprite.setTextureRect(IntRect(0,0,0,0));
            dx = 0;
            visible = false;
        }

        control(time);

        checkCollisionWithMap(dx, 0);
        x += dx*time;
        y += dy*time;

        checkCollisionWithMap(0, dy);
        dy = dy + 0.0015*time;

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
bool HardEnemy::shrek_near(Entity* shrek)
{
    if (shrek -> name == "Player1")
    {
        float dist = sqrt((shrek -> x - x)*(shrek -> x - x) + (shrek -> y - y)*(shrek -> y - y));
        if (dist < 300) {

            is_near = true;
            visible = true;
            if (shrek -> x - x > 0)
                dx = 0.06;
            else dx = -0.06;

            return true;
        }
        else
        {
            if (x - start_x > 0)
                dx = -0.05;
            else dx = 0.05;
            is_near = false;

            return false;
        }

    }
}