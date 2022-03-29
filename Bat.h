#ifndef BAT_H
#define BAT_H

#include "Enemy.h"

class Bat : public Enemy {
public :
    Bat(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel);
    ~Bat();

};

#endif // BAT_H
