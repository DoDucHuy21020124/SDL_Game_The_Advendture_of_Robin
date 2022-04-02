#ifndef BONUS_MANAGER_H
#define BONUS_MANAGER_H

#include <vector>
#include "Bonus.h"

class BonusManager {
private :
    std::vector<Bonus*> bonus_list;
    Uint64 time_start;
    Uint64 time_wait;

public :
    BonusManager();
    ~BonusManager();

    Bonus* make_bonus();
    void init_bonus();
    void remove_bonus(const int& index);
    void check_bonus();
    void update();
    void draw();
    void clean_up();
};

#endif // BONUS_MANAGER_H
