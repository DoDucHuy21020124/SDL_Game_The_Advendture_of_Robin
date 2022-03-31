#ifndef ENEMY_H
#define ENEMY_H

#include "TextureManager.h"

class Enemy : public TextureManager {
protected :
    Vector2D velocity;
    int hp;
    bool is_destroyed;
    bool is_destroying;

public :
    Enemy(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel);
    ~Enemy();

    int get_hp() const {return hp;}
    void set_hp(const int& hp_) {hp = hp_;}
    bool get_is_destroyed() const {return is_destroyed;}
    void set_is_destroyed(const bool& is_destroyed_) {is_destroyed = is_destroyed_;}
    bool get_is_destroying() const {return is_destroying;}
    void set_is_destroying(const bool& is_destroying_) {is_destroying = is_destroying_;}

    void handle_move();
    virtual void update();
};

#endif // ENEMY_H
