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
    TextureManager* collision_effect;
    bool is_destroyed;
    int weapon_type;
    Uint64 time_special_weapon;
    Uint64 time_start;

public :
    Character(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel);
    ~Character();

    void set_velocity(const Vector2D& vel) {velocity = vel;}
    std::vector<Weapon*> get_weapon() const {return weapon;}
    void set_weapon(const std::vector<Weapon*>& weapon_) {weapon = weapon_;}
    TextureManager* get_collision_effect() const {return collision_effect;}
    bool get_is_destroyed() const {return is_destroyed;}
    void set_is_destroyed(const bool& is_destroyed_) {is_destroyed = is_destroyed_;}
    int get_weapon_type() const {return weapon_type;}
    void set_weapon_type(const int& weapon_type_) {weapon_type = weapon_type_;}
    void set_time_start(const Uint64& time) {time_start = time;}

    void init_weapon(int weapon_type_);
    void remove_weapon(const int& index);
    void check_weapon();
    void handle_event();
    void handle_move();
    void update_image();
    void play_collision_effect();
    void update();
    void draw();

};

#endif // CHARACTER_h
