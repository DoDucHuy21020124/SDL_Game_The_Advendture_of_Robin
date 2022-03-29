#include "Character.h"
#include "Game.h"

Character::Character(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel) : TextureManager(filePath, position, numFrame, speed) {
    velocity = vel;
    jump_speed = int(velocity.y);
    on_ground = true;
}

Character::~Character() {

}

void Character::handle_move() {
    if ( move_direction.move_right == 1 ) destRect.x += int(velocity.x);
    if ( move_direction.move_left == 1 ) destRect.x -= int(velocity.x);

    if ( destRect.x < 0 ) destRect.x += int(velocity.x);
    else if ( destRect.x + destRect.w > SCREEN_WIDTH ) destRect.x -= int(velocity.x);

    if ( !on_ground ) {
        destRect.y -= jump_speed;
        jump_speed -= 1;
    }
    else {
        jump_speed = int(velocity.y);
    }

    destRect.y += GRAVITY_CHARACTER;
    if ( destRect.y > GROUND_HEIGHT - 100 ) destRect.y = GROUND_HEIGHT - 100;

    if ( destRect.y == GROUND_HEIGHT - 100 ) on_ground = true;
}

void Character::handle_event() {
    if ( Game::g_event.type == SDL_KEYDOWN ) {
        switch(Game::g_event.key.keysym.sym) {
        case SDLK_UP :
            if ( on_ground ) {
                on_ground = false;
            }
            break;
        case SDLK_DOWN :
            break;
        case SDLK_RIGHT :
            move_direction.move_right = 1;
            move_direction.move_left = 0;
            break;
        case SDLK_LEFT :
            move_direction.move_right = 0;
            move_direction.move_left = 1;
            break;
        default :
            break;
        }
    }

    if ( Game::g_event.type == SDL_KEYUP ) {
        switch(Game::g_event.key.keysym.sym) {
        case SDLK_UP :
            break;
        case SDLK_DOWN :
            break;
        case SDLK_RIGHT :
            move_direction.move_right = 0;
            break;
        case SDLK_LEFT :
            move_direction.move_left = 0;
            break;
        default :
            break;
        }
    }

    if ( Game::g_event.type == SDL_MOUSEBUTTONDOWN ) {
        if ( Game::g_event.button.button == SDL_BUTTON_LEFT ) {
            move_direction.attack = 1;
        }
    }

    if ( Game::g_event.type == SDL_MOUSEBUTTONUP ) {
        if ( Game::g_event.button.button == SDL_BUTTON_LEFT ) {
            move_direction.attack = 0;
        }
    }
}

void Character::update_image() {
    if ( !on_ground && file_path != "image\\archer_angle.png") set_file_path("image\\archer_angle.png", 4);
    if ( on_ground ) {
        if ( file_path == "image\\archer_angle.png") {
            set_file_path("image\\archer_walk.png", 8);
        }
        else if ( file_path == "image\\archer_normal.png" && frame >= num_frame - 1 && move_direction.attack != 1 ) {
            set_file_path("image\\archer_walk.png", 8);
        }
        else if ( move_direction.attack == 1 && file_path != "image\\archer_normal.png" ) {
            set_file_path("image\\archer_normal.png", 4);
        }
    }
}

void Character::update() {
    handle_event();
    handle_move();
    update_image();
    TextureManager::update();
}
