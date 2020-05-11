#ifndef PROJECT_HARDENEMY_H
#define PROJECT_HARDENEMY_H
#include "entity.h"

class HardEnemy :public Entity{
public:
    HardEnemy(Image &image, float X, float Y,int W,int H,String Name);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);
    void update(float time, Map map){};
    void collision(Entity* enemy);
    float start_x;
    float start_y;

    void control(float time);
    float moveTimer;

    bool shrek_near(Entity* shrek);
    bool visible;
    bool is_near;
};

#endif //PROJECT_HARDENEMY_H
