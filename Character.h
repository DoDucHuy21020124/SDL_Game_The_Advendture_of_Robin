#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "TextureManager.h"
#include "Vector2D.h"
#include "Weapon.h"

const int GRAVITY_CHARACTER = 1;

struct move_type {
    int move_right = 0;
    int move_left = 0;
    int jump = 0;
    int attack = 0;
};

class Character : public TextureManager {
private :
    Vector2D velocity;
    int jump_speed;
    bool on_ground;
    move_type move_direction;
    std::vector<Weapon*> weapon;

public :
    Character(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel);
    ~Character();

    void set_velocity(const Vector2D& vel) {velocity = vel;}

    void init_weapon();
    void remove_weapon(const int& index);
    void check_weapon();
    void handle_event();
    void handle_move();
    void update_image();
    void update();
    void draw();

};

#endif // CHARACTER_h
