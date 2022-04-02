#ifndef BONUS_H
#define BONUS_H

#include "TextureManager.h"

class Bonus : public TextureManager {
private :
    Vector2D velocity;
    bool is_move;

public :
    Bonus(const char* filePath, Vector2D position, int numFrame, int speed_, Vector2D vel);
    ~Bonus();

    bool get_is_move() const {return is_move;}
    void set_is_move(const bool& is_move_) {is_move = is_move_;}

    void handle_move();
    void update();
};


#endif // BONUS_H
