#ifndef GOAT_H
#define GOAT_H

#include <vector>
#include "Enemy.h"
#include "Weapon.h"

const int DISTANCE_WEAPON = 300;
const int NUM_ATTACK = 3;

class Goat : public Enemy {
private :
    std::vector<Weapon*> weapon;
    bool is_attacking;
    bool is_appear;
    int num_attack;
    int time_wait;
    int time_appear;
    Uint64 time_start;

public :
    Goat(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel);
    ~Goat();

    void init_weapon(const int& x_pos);
    void remove_weapon(const int& index);
    void check_weapon();
    void update_image();
    void attack(const int& x_pos);
    void appear();
    void update();
    void draw();
};

#endif // GOAT_H

