#include "Dragon.h"
#include "GeneralFunction.h"

Dragon::Dragon(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel) : Enemy(filePath, position, numFrame, speed, vel) {

}

Dragon::~Dragon() {
    clear_up();
}

void Dragon::init_weapon() {
    Weapon* fire = new Weapon("image\\fire_ball.png", Vector2D(destRect.x + destRect.w, destRect.y + destRect.h/1.1), 4, 80, Vector2D(5, 0), 10);
    weapon.push_back(fire);
}

void Dragon::remove_weapon(const int& index) {
    if ( index < weapon.size() && weapon.size() > 0 ) {
        weapon.erase(weapon.begin() + index);
    }
}

void Dragon::check_weapon() {
    for ( int i = 0; i < weapon.size(); ) {
        if ( weapon[i]->get_xpos() > SCREEN_WIDTH ) weapon[i]->set_is_move(false);
        if ( !weapon[i]->get_is_move() ) remove_weapon(i);
        else ++i;
    }
}

void Dragon::update() {
    Enemy::update();
    if ( frame == 20 ) {
        play_sound_effect("music\\dragon_roar.wav");
        init_weapon();
    }
    check_weapon();
    for ( int i = 0; i < weapon.size(); ++i ) {
        weapon[i]->update();
    }
}

void Dragon::draw(SDL_RendererFlip render_flip) {
    Enemy::draw(render_flip);
    for ( int i = 0; i < weapon.size(); ++i ) {
        weapon[i]->draw();
    }
}

void Dragon::clear_up() {
    weapon.clear();
}
