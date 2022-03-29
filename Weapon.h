#ifndef WEAPON_H
#define WEAPON_H

#include "TextureManager.h"

class Weapon : public TextureManager {
private :
    Vector2D velocity;
    bool is_move;

public :
    Weapon(const char* filePath, Vector2D position, int numFrame, Vector2D vel);
    ~Weapon();

    bool get_is_move() const {return is_move;}
    void set_is_move(const bool& is_move_) {is_move = is_move_;}

    void handle_move();
    void update();

};

#endif // WEAPON_H
