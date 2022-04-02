#ifndef BONUS_H
#define BONUS_H

#include "TextureManager.h"

class Bonus : public TextureManager {
private :
    Vector2D velocity;
    bool is_move;
    int bonus_type;

public :
    Bonus(const char* filePath, Vector2D position, int numFrame, int speed_, Vector2D vel, int bonus_type_);
    ~Bonus();

    bool get_is_move() const {return is_move;}
    void set_is_move(const bool& is_move_) {is_move = is_move_;}
    int get_bonus_type() const {return bonus_type;}

    void handle_move();
    void update();
};


#endif // BONUS_H
