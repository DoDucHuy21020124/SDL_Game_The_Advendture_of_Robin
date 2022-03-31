#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <vector>
#include "Bat.h"
#include "Wolf.h"

class EnemyManager {
private :
    std::vector<Enemy*> enemy_list;
    int time_appear_bat;
    int time_appear_wolf;
    Uint64 time_start_bat;
    Uint64 time_start_wolf;

public :
    EnemyManager();
    ~EnemyManager();

    void set_enemy_list(const std::vector<Enemy*>& enemy_list_) {enemy_list = enemy_list_;}
    std::vector<Enemy*> get_enemy_list() const {return enemy_list;}

    void init_enemy_bat(const int& x, const int& y);
    void init_enemy_wolf();
    void remove_enemy(const int& index);
    void check_enemy();
    void update();
    void draw();
    void clear_up();
};

#endif // ENEMY_MANAGER_H
