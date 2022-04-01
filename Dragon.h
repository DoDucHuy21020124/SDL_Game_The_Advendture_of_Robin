#ifndef DRAGON_H
#define DRAGON_H

#include <vector>
#include "Enemy.h"
#include "Weapon.h"

class Dragon : public Enemy {
private :
    std::vector<Weapon*> weapon;

public :
    Dragon(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel);
    ~Dragon();

    std::vector<Weapon*> get_weapon() const {return weapon;}
    void set_weapon(const std::vector<Weapon*>& weapon_) {weapon = weapon_;}

    void init_weapon();
    void remove_weapon(const int& index);
    void check_weapon();
    void update();
    void draw(SDL_RendererFlip render_flip);
    void clear_up();
};

#endif // DRAGON_H
