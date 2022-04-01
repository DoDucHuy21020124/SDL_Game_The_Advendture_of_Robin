#include "Wolf.h"

Wolf::Wolf(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel) : Enemy(filePath, position, numFrame, speed, vel) {
    hp = 3;
    score = 5;

    collision_effect = new TextureManager("image\\blood.png", Vector2D(0, 0), 6, 120);
}

Wolf::~Wolf() {

}

void Wolf::play_collision_effect() {
    collision_effect->draw();
}
