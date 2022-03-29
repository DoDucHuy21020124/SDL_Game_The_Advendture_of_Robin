#ifndef ENEMY_H
#define ENEMY_H

#include "TextureManager.h"

class Enemy : public TextureManager {
protected :
    Vector2D velocity;

public :
    Enemy(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel);
    ~Enemy();

    void handle_move();
    virtual void update();
};

#endif // ENEMY_H
