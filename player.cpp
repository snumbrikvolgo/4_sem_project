#include "player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

Player::Player(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name)
{
    currentFrame = 0;
    score = 0;
    state = stay;
    if (name == "Player1"){
        sprite.setTextureRect(IntRect(43, 0, w, h));
    }
}

void Player::control(float time)
{
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        state = left;
        speed = -0.1;
        currentFrame += 0.005*time;
        if (currentFrame > 3) currentFrame -= 3;
            sprite.setTextureRect(IntRect(43 * int(currentFrame)+79, 68, 43, 50));
        sprite.setScale(-1.0f, 1.0f);
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        state = right;
        speed = 0.1;
        currentFrame += 0.005 * time;
        if (currentFrame > 4) currentFrame -= 4;
        sprite.setTextureRect(IntRect(43 * int(currentFrame) + 79, 68, 43, 50));
        sprite.move(0.1 * time, 0);
        sprite.setScale(1.0f, 1.0f);
    }

    if ((Keyboard::isKeyPressed(Keyboard::Up)) && onGround) {
        state = jump;
        dy = -0.8;
        onGround = false;
        currentFrame += 0.005 * time;
        if (currentFrame > 4) currentFrame -= 4;
        sprite.setTextureRect(IntRect(36 * int(currentFrame) + 98, 130, 36, 50));
        sprite.move(0, -0.1 * time);
        sprite.setScale(1.0f, 1.0f);
    }

    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        state = down;
        speed = 0.1;
        currentFrame += 0.005 * time;
        sprite.move(0, 0.1 * time);
        sprite.setTextureRect(IntRect(195, 250, 37, 42));
    }
}
void Player::checkCollisionWithMap(float Dx, float Dy, Map m)
{
    //printf("shrek по  в котроле мапа y %f\n", y);
    for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j<(x + w) / 32; j++)
        {
            if (m.tiledMap[i][j] == '0' || m.tiledMap[i][j] == '1' || m.tiledMap[i][j] == '2' ||
                m.tiledMap[i][j] == '3' || m.tiledMap[i][j] == '4' || m.tiledMap[i][j] == '5'
                                                                || m.tiledMap[i][j] == '6')
            {
                if (Dy>0)
                    { y = i * 32 - h;  dy = 0; onGround = true; }
                if (Dy<0)
                    { y = i * 32 + 32;  dy = 0; }
                if (Dx>0)
                    { x = j * 32 - w; }
                if (Dx<0)
                    { x = j * 32 + 32; }
            }

            if (m.tiledMap[i][j] == 'w' || m.tiledMap[i][j] == 'c')
            {
                speed = 0;
                onGround = false;
                health = 0;
            }

            if (m.tiledMap[i][j] == 'm')
            {
                m.tiledMap[i][j] = ' ';
                score++;
                //printf("score = %d\n", score);
            }


        }
}

void Player::death(float time)
{
    currentFrame += 0.005 * time;
    //if (currentFrame > 13) currentFrame -= 13;
        sprite.setTextureRect(IntRect(36 * int(currentFrame) + 92, 447, 40, 50));
    sprite.setScale(1.0f, 1.0f);
}
void Player::update(float time){};

void Player::update(float time, Map m)
{
    if(!life) {
        speed = 0;
        dx = 0;
        dy = 0;
        return;
    }

    control(time);

    switch (state)
    {
        case right:dx = speed; break;
        case left:dx = speed; break;
        case up: break;
        case down: dx = 0; break;
        case stay: break;
    }

    x += dx*time;
    checkCollisionWithMap(dx, 0, m);

    //("time %f before 4th call dy %f\n", time, dy);
    y += dy*time;
    checkCollisionWithMap(0, dy, m);

    sprite.setPosition(x + w / 2, y + h /1.5 + 3);

    if (health <= 0)
        { life = false; }
    if (!isMove)
         speed = 0;

    setPlayerCoordinateForView(x, y);


    dy = dy + 0.0007*time;
}


void Player::collision(Entity* enemy)
{
    if (enemy -> name == "EasyEnemy")
    {
        if (abs((x - (enemy)->x)) < 20 && onGround) {
            printf("enemy x");
            health -= 2;
        }
        if (abs(y  - enemy->y) < 100 && abs(x - enemy -> x) < 100 &&
                 (!onGround)) {
            dy = -0.2;
        }
    }

}