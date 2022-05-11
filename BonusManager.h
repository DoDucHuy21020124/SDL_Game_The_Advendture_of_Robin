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

    std::vector<Bonus*> get_bonus_list() const {return bonus_list;}
    void set_bonus_list(const std::vector<Bonus*>& bonus_list_) {bonus_list = bonus_list_;}
    Uint64 get_time_wait() const {return time_wait;}
    void set_time_wait(const Uint64 time_wait_) {time_wait = time_wait_;}

    Bonus* make_bonus(int bonus_type);
    void init_bonus();
    void remove_bonus(const int& index);
    void check_bonus();
    void update();
    void draw();
    void clean_up();
};

#endif // BONUS_MANAGER_H
