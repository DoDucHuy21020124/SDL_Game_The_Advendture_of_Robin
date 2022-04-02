#include "Bonus.h"

Bonus::Bonus(const char* filePath, Vector2D position, int numFrame, int speed_, Vector2D vel) : TextureManager(filePath, position, numFrame, speed_) {
    velocity = vel;
    is_move = true;
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

