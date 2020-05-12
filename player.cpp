#include "player.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>

using namespace sf;

void Player::collision(Entity* enemy){
    if (enemy -> name == "EasyEnemy" )
    {
        if (abs((x - (enemy)->x)) < 50 && onGround) {
            health -= 0;
        }
        if (abs(y  - enemy->y) < 100 && abs(x - enemy -> x) < 100 &&
            (!onGround)) {
            dy = -0.2;
        }
    }
    else if (enemy -> name == "HardEnemy")
    {
        if (abs((x - (enemy)->x)) < 50 && onGround) {
            health -= 0;
        }

        if (abs(y  - enemy->y) < 100 && abs(x - enemy -> x) < 50 &&
            (!onGround)) {
            dy = -0.2;
        }
    }

}
Player::Player(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name)
{
    currentFrame = 0;
    score = 0;
    state = stay;
    if (name == "Player1"){
        sprite.setTextureRect(IntRect(43, 0, w, h));
    }

    screamBuffer.loadFromFile("music/Scream.wav");
    scream.setBuffer(screamBuffer);

    stone = false;
}

void Player::control(float time)
{
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        state = left;
        speed = -0.1;
        play_animation(4, 79, 50, 43, 68, 1, time);
        sprite.move(0.1 * time, 0);
        sprite.setScale(-1.0f, 1.0f);
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        state = right;
        speed = 0.1;
        play_animation(4, 79, 50, 43, 68, 1, time);
        sprite.move(0.1 * time, 0);;
        sprite.setScale(1.0f, 1.0f);
    }

    if ((Keyboard::isKeyPressed(Keyboard::Up)) && onGround) {
        state = jump;
        dy = -0.8;
        onGround = false;
        sprite.move(0, -0.1 * time);
        play_animation(4, 98, 50, 36, 130, 1, time);
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
            }
            else if (m.tiledMap[i][j] == 's')
            {
                m.tiledMap[i][j] = ' ';
                stone = true;

            }

        }
}

void Player::death(float time)
{
    scream.play();
    play_animation(13, 92, 50, 40, 447, 0, time);
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

    y += dy*time;
    checkCollisionWithMap(0, dy, m);

    sprite.setPosition(x + w / 2, y + h /1.5 + 3);

    if (health <= 0)
        {
            life = false;
        }
    if (!isMove)
         speed = 0;

    setPlayerCoordinateForView(x, y);
    dy = dy + 0.0015*time;
}
