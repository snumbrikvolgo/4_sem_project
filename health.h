//
// Created by snumbrikvolgo on 24.05.20.
//
#include <SFML/Graphics.hpp>

using namespace sf;

class Health{
public:
//    Image hb;
//    Texture ht;
    int maximum;

    RectangleShape bar;

    Health(int health);

    void update(int cur, float x, float y);

    void set(float x, float y);
};
