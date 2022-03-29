#ifndef WEAPON_H
#define WEAPON_H

#include "TextureManager.h"

class Weapon : public TextureManager {
private :
    Vector2D velocity;

public :
    Weapon(const char* filePath, Vector2D position, int numFrame, Vector2D vel);
    ~Weapon();

    void handle_move();
    void update();

};

#endif // WEAPON_H
