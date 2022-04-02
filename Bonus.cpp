#include "Bonus.h"

Bonus::Bonus(const char* filePath, Vector2D position, int numFrame, int speed_, Vector2D vel, int bonus_type_) : TextureManager(filePath, position, numFrame, speed_) {
    velocity = vel;
    is_move = true;
    bonus_type = bonus_type_;
}

Bonus::~Bonus() {

}

void Bonus::handle_move() {
    destRect.x += int(velocity.x);
    destRect.y += int(velocity.y);
}

void Bonus::update() {
    handle_move();
}

