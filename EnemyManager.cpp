#include "EnemyManager.h"
#include "GeneralFunction.h"

EnemyManager::EnemyManager() {
    time_appear_bat = 5000;
    time_appear_wolf = 10000;
    time_start_bat = SDL_GetTicks64();
    time_start_wolf = SDL_GetTicks64();
}

EnemyManager::~EnemyManager() {
    clear_up();
}

void EnemyManager::init_enemy_bat(const int& x, const int& y) {
    if ( SDL_GetTicks64() - time_start_bat >= time_appear_bat ) {
        int ypos = rand()%(GROUND_HEIGHT - 32);
        float vel_x = -(SCREEN_WIDTH - x)/100;
        float vel_y = (-(ypos - y)/100);
        Enemy* bat = new Bat("image\\bat.png", Vector2D(SCREEN_WIDTH, ypos), 4, 80, Vector2D(vel_x, vel_y));
        enemy_list.push_back(bat);
        time_start_bat = SDL_GetTicks64();
    }
}

void EnemyManager::init_enemy_wolf() {
    if ( SDL_GetTicks64() - time_start_wolf >= time_appear_wolf ) {
        Enemy* wolf = new Wolf("image\\wolf.png", Vector2D(SCREEN_WIDTH, GROUND_HEIGHT - 64), 8, 80, Vector2D(-8, 0));
        enemy_list.push_back(wolf);
        time_start_wolf = SDL_GetTicks64();
    }
}

void EnemyManager::remove_enemy(const int& index) {
    if ( index >= 0 && index < enemy_list.size() ) {
        enemy_list.erase(enemy_list.begin() + index);
    }
}

void EnemyManager::check_enemy() {
    for ( int i = 0; i < enemy_list.size(); ) {
        if ( enemy_list[i]->get_is_destroyed() ) {
            remove_enemy(i);
        }
        else ++i;
    }
}

void EnemyManager::update() {
    check_enemy();
    for ( int i = 0; i < enemy_list.size(); ++i ) {
        enemy_list[i]->update();
        if ( enemy_list[i]->get_is_destroying() ) {
            enemy_list[i]->get_collision_effect()->update();
            if ( enemy_list[i]->get_collision_effect()->get_frame() >= enemy_list[i]->get_collision_effect()->get_num_frame() - 1) {
                enemy_list[i]->set_is_destroying(false);
                enemy_list[i]->set_is_destroyed(true);
            }
        }
    }
}

void EnemyManager::draw() {
    for ( int i = 0; i < enemy_list.size(); ++i ) {
        enemy_list[i]->draw();
        if ( enemy_list[i]->get_is_destroying() ) {
            enemy_list[i]->play_collision_effect();
        }
    }
}

void EnemyManager::clear_up() {
    enemy_list.clear();
}
