#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include <list>
#include "entity.h"
#include "map.h"


void gameRunning();
bool Start();
void collisionDetection(std::list<Entity*>& entities, float time, Map map);

#endif //PROJECT_GAME_H
