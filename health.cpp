//
// Created by snumbrikvolgo on 24.05.20.
//

#include "health.h"
#include <iostream>

Health::Health(int health) {
    bar.setFillColor(Color::Green);
    maximum = health;
    //std::cout << "hp created\n";
};

void Health::update(int cur, float x, float y)
{
    if (cur > 0)
    {
        if (cur <= 0.7* maximum)
        {
            bar.setFillColor(Color::Yellow);

        }
        else if (cur <= 0.3*maximum)
        {
            bar.setFillColor(Color::Red);
        }
        bar.setSize(Vector2f(cur*0.7, 10));
        set(x, y);
    }
}

void Health::set(float x, float y) {
    bar.setPosition(x, y);
}
