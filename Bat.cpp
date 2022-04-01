#include "Bat.h"

Bat::Bat(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel) : Enemy(filePath, position, numFrame, speed, vel) {
    hp = 2;
    score = 2;

    collision_effect = new TextureManager("image\\blood.png", Vector2D(0, 0), 6, 120);
}

Bat::~Bat() {

}

void Bat::play_collision_effect() {
    collision_effect->draw();
}
