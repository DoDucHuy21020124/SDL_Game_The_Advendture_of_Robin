#ifndef ENEMY_H
#define ENEMY_H

#include "TextureManager.h"

class Enemy : public TextureManager {
protected :
    Vector2D velocity;
    int hp;
    int score;
    bool is_destroyed;
    bool is_destroying;

public :
    Enemy(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel);
    ~Enemy();

    int get_hp() const {return hp;}
    void set_hp(const int& hp_) {hp = hp_;}
    int get_score() const {return score;}
    bool get_is_destroyed() const {return is_destroyed;}
    void set_is_destroyed(const bool& is_destroyed_) {is_destroyed = is_destroyed_;}
    bool get_is_destroying() const {return is_destroying;}
    void set_is_destroying(const bool& is_destroying_) {is_destroying = is_destroying_;}
    Vector2D get_velocity() const {return velocity;}
    void set_velocity(const Vector2D& vel) {velocity = vel;}

    void handle_move();
    virtual TextureManager* get_collision_effect(){};
    virtual void play_collision_effect(){};
    virtual void update();
};

#endif // ENEMY_H
