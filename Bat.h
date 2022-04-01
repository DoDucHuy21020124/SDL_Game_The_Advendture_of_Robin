#ifndef BAT_H
#define BAT_H

#include "Enemy.h"

class Bat : public Enemy {
private :
    TextureManager* collision_effect;

public :
    Bat(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel);
    ~Bat();

    TextureManager* get_collision_effect() {return collision_effect;}
    void play_collision_effect();
};

#endif // BAT_H
