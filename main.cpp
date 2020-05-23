#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include <time.h>

sf::View view;

using namespace sf;

int main()
{
    srand(time(NULL));
    gameRunning();
    return 0;
}
