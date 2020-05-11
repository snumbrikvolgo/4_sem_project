#include "menu.h"

bool menu(RenderWindow & window) {

    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;

    menuTexture1.loadFromFile("images/111.png");
    menuTexture3.loadFromFile("images/333.png");
    menuBackground.loadFromFile("images/swamp.jpg");

    Music music;
    music.openFromFile("music/shrek.ogg");

    Sprite menu1(menuTexture1), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);

    bool isMenu = 1;
    int menuNum = 0;

    menu1.setPosition(100, 30);
    menu3.setPosition(100, 150);
    menuBg.setScale(0.5f,0.5f);
    menuBg.setPosition(0, 0);

    music.play();

    while (isMenu)
    {

        menu1.setColor(Color::White);
        menu3.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(172, 183, 142));

        if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Green); menuNum = 1; }
        if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Green); menuNum = 3; }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) {isMenu = false; return true; }
            if (menuNum == 3)  {
                //printf("close\n");
                window.close();
                music.stop();

                isMenu = false;
                return false;

            }

        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu3);

        window.display();
    }
}
