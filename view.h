//
// Created by snumbrikvolgo on 22.04.20.
//

#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H
#pragma once
#include <SFML/Graphics.hpp>

extern sf::View view;
void setPlayerCoordinateForView(float x,float y);

//void viewmap(float time) { //функция для перемещения камеры по карте. принимает время sfml
//
//
//    if (Keyboard::isKeyPressed(Keyboard::D)) {
//        view.move(0.1*time, 0);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
//    }
//
//    if (Keyboard::isKeyPressed(Keyboard::S)) {
//        view.move(0, 0.1*time);//скроллим карту вниз (см урок, когда мы двигали героя - всё тоже самое)
//    }
//
//    if (Keyboard::isKeyPressed(Keyboard::A)) {
//        view.move(-0.1*time, 0);//скроллим карту влево (см урок, когда мы двигали героя - всё тоже самое)
//    }
//    if (Keyboard::isKeyPressed(Keyboard::W)) {
//        view.move(0, -0.1*time);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
//    }
//
//
//}


//void changeview(){
//
//
//    if (Keyboard::isKeyPressed(Keyboard::U)) {
//        view.zoom(1.0100f); //масштабируем, уменьшение
//        //view.zoom(1.0006f); //тоже самое помедленнее соответственно
//    }
//
//    if (Keyboard::isKeyPressed(Keyboard::R)) {
//        //view.setRotation(90);//сразу же задает поворот камере
//        view.rotate(1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
//    }
//
//
//    if (Keyboard::isKeyPressed(Keyboard::I)) {
//        view.setSize(640, 480);//устанавливает размер камеры (наш исходный)
//    }
//
//    if (Keyboard::isKeyPressed(Keyboard::P)) {
//        view.setSize(540, 380);//например другой размер
//    }
//
//
//    if (Keyboard::isKeyPressed(Keyboard::Q)) {
//        view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//таким образом делается раздельный экран для игры на двоих. нужно только создать ещё один объект View и привязывать к нему координаты игрока 2.
//    }
//
//
//
//}

#endif //PROJECT_VIEW_H
