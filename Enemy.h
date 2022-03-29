#ifndef ENEMY_H
#define ENEMY_H

#include "TextureManager.h"

class Enemy : public TextureManager {
private :
    Vector2D velocity;

public :
    Enemy(const char* filePath, Vector2D position, int numFrame, Vector2D vel);
    ~Enemy();

    void handle_move();
    void update();
};

#endif // ENEMY_H
