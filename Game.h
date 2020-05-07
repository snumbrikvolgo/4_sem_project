#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "map.h"
#include "entity.h"

void gameRunning();
bool Start();


void collisionDetection(std::list<Entity*>& entities, float time, Map map);
#endif //PROJECT_GAME_H
