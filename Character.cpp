#include "Character.h"
#include "Game.h"

Character::Character(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel) : TextureManager(filePath, position, numFrame, speed) {
    velocity = vel;
    jump_speed = int(velocity.y);
    on_ground = true;
    collision_effect = new TextureManager("image\\blood.png", Vector2D(0, 0), 6, 200);
    is_destroyed = false;
    weapon_type = 0;
    time_special_weapon = 10000;
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

void Character::init_weapon(int weapon_type_) {
    switch(weapon_type_) {
    case 0:
        {
            Weapon* arrow = new Weapon("image\\arrow.png", Vector2D(destRect.x + destRect.w, destRect.y + destRect.h/4), 6, 80, Vector2D(5, 0), 1);
            weapon.push_back(arrow);
            break;
        }
    case 1:
        {
            Weapon* arrow1 = new Weapon("image\\arrow.png", Vector2D(destRect.x + destRect.w, destRect.y + destRect.h/4), 6, 80, Vector2D(5, 5), 1);
            Weapon* arrow2 = new Weapon("image\\arrow.png", Vector2D(destRect.x + destRect.w, destRect.y + destRect.h/4), 6, 80, Vector2D(5, 0), 1);
            Weapon* arrow3 = new Weapon("image\\arrow.png", Vector2D(destRect.x + destRect.w, destRect.y + destRect.h/4), 6, 80, Vector2D(5, -5), 1);
            weapon.push_back(arrow1);
            weapon.push_back(arrow2);
            weapon.push_back(arrow3);
        }
        break;
    case 2:
        {
            Weapon* arrow = new Weapon("image\\fire_arrow.png", Vector2D(destRect.x + destRect.w, destRect.y + destRect.h/4), 6, 80, Vector2D(5, 0), 3);
            weapon.push_back(arrow);
        }
        break;
    default:
        break;
    }
}

void Character::remove_weapon(const int& index) {
    if ( index < weapon.size() && weapon.size() > 0 ) {
        weapon.erase(weapon.begin() + index);
    }
}

void Character::check_weapon() {
    for ( int i = 0; i < weapon.size(); ) {
        if ( weapon[i]->get_xpos() > SCREEN_WIDTH ) weapon[i]->set_is_move(false);
        if ( !weapon[i]->get_is_move() ) remove_weapon(i);
        else ++i;
    }
    if ( weapon_type != 0 && SDL_GetTicks64() - time_start > time_special_weapon ) {
        weapon_type = 0;
    }
}

void Character::handle_event() {
    if ( Game::g_event.type == SDL_KEYDOWN ) {
        switch(Game::g_event.key.keysym.sym) {
        case SDLK_w :
            if ( on_ground ) {
                on_ground = false;
            }
            break;
        case SDLK_s :
            break;
        case SDLK_d :
            move_direction.move_right = 1;
            move_direction.move_left = 0;
            break;
        case SDLK_a :
            move_direction.move_right = 0;
            move_direction.move_left = 1;
            break;
        default :
            break;
        }
    }

    if ( Game::g_event.type == SDL_KEYUP ) {
        switch(Game::g_event.key.keysym.sym) {
        case SDLK_w :
            break;
        case SDLK_s :
            break;
        case SDLK_d :
            move_direction.move_right = 0;
            break;
        case SDLK_a :
            move_direction.move_left = 0;
            break;
        default :
            break;
        }
    }

    if ( Game::g_event.type == SDL_MOUSEBUTTONDOWN ) {
        if ( Game::g_event.button.button == SDL_BUTTON_LEFT ) {
            play_sound_effect("music\\arrow.wav");
            move_direction.attack = 1;
            init_weapon(weapon_type);
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

void Character::play_collision_effect() {
    collision_effect->draw();
    collision_effect->update();
}

void Character::update() {
    handle_event();
    handle_move();
    update_image();
    check_weapon();
    TextureManager::update();
    for ( int i = 0; i < weapon.size(); ++i ) {
        weapon[i]->update();
    }
}

void Character::draw() {
    TextureManager::draw();
    for ( int i = 0; i < weapon.size(); ++i ) {
        weapon[i]->draw();
    }
}
