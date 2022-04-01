#ifndef WEAPON_H
#define WEAPON_H

#include "TextureManager.h"

class Weapon : public TextureManager {
private :
    Vector2D velocity;
    bool is_move;
    int damage;

public :
    Weapon(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel, int damage_);
    ~Weapon();

    int get_damage() const {return damage;}
    void set_damage(const int& damage_){damage = damage_;}
    bool get_is_move() const {return is_move;}
    void set_is_move(const bool& is_move_) {is_move = is_move_;}

    void handle_move();
    void update();

};

#endif // WEAPON_H
