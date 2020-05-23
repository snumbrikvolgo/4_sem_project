//
// Created by snumbrikvolgo on 14.05.20.
//

#include "FlyingEnemy.h"
#include <math.h>
#include <time.h>

Raven::Raven(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name)
{
    if (name == "Raven")
    {
        sprite.setTextureRect(IntRect(0, 44, 35, 60));
        dx = 0.06;
        moveTimer = 0;
        onGround = false;
        is_near = true;
        nearTimer = 0;

        ro_dah = false;
        shrek_x = X;
        shrek_y = Y;
    }

}

void Raven::checkCollisionWithMap(float Dx, float Dy) {
    float next_position_x = x + dx;
    int j = next_position_x / 32;
    int i = (y) / 32;

    if (TileMap[i][j] != ' ' || TileMap[i+1][j] != ' ' )
    {
        dx *= -1;
    }

}
void Raven::collision(Entity* enemy){
    if (enemy -> name == "EasyEnemy" || enemy -> name == "HardEnemy" || enemy -> name == "Raven")
    {
        if (dx > 0)
            x -= w / 2;
        else x += w / 2;
    }
    else if (enemy -> name == "Player1")
    {
        if (Keyboard::isKeyPressed(Keyboard::X)) {
            ro_dah = true;
            is_near = false;
            if (enemy -> x > x) {

                dx = -0.2;
            }
            else dx = 0.2;
        }
    }
}

void Raven::control(float time)
{
    if (dx < 0) {
        sprite.move(-0.1 * time, 0);
        play_animation(2, 76, 70, 46, 40, 1, time);
        sprite.setScale(-1.0f, 1.0f);
    }

    if (dx > 0) {
        sprite.move(0.1 * time, 0);
        play_animation(2, 76, 70, 46, 40, 1, time);
        sprite.setScale(1.0f, 1.0f);
    }

}

void Raven::update(float time)
{
    if (name == "Raven")
    {
        control(time);
        if (ro_dah)
            is_near = false;
        if (!is_near)
        {
            moveTimer += time;

            if (moveTimer > 8000)
            {
                dx *= -1;
                moveTimer = 0;
            }
        }

        checkCollisionWithMap(dx, 0);
        x += dx*time;
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


bool Raven::shrek_near(Entity* shrek)
{
    if (shrek -> name == "Player1")
    {
        float dist = sqrt((shrek -> x - x)*(shrek -> x - x) + (shrek -> y - y)*(shrek -> y - y));
        if (dist < 100 && !ro_dah) {
            shrek_x = shrek -> x;
            shrek_y = shrek -> y;
            is_near = true;
            {
                if (shrek -> dx > 0)
                {
                    x = shrek_x + 32;
                    y = shrek_y;
                }
                else {
                    x = shrek_x -32;
                    y = shrek_y;
                }
                if (shrek -> dy < 0)
                {
                    y = shrek_y - 32;
                }
            }

            return true;
        }
        else
        {
            is_near = false;
            return false;
        }

    }
}
