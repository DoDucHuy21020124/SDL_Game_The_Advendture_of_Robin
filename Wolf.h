#ifndef WOLF_H
#define WOLF_H

#include "Enemy.h"

class Wolf : public Enemy {
private:
    TextureManager* collision_effect;

public :
    Wolf(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel);
    ~Wolf();

    TextureManager* get_collision_effect() {return collision_effect;}
    void play_collision_effect();
};

#endif // WOLF_H
