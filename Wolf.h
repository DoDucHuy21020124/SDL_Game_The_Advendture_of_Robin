#ifndef WOLF_H
#define WOLF_H

#include "Enemy.h"

class Wolf : public Enemy {
public :
    Wolf(const char* filePath, Vector2D position, int numFrame, Vector2D vel);
    ~Wolf();
};

#endif // WOLF_H
