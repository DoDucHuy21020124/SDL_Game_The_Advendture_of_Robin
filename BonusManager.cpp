#include "BonusManager.h"
#include "GeneralFunction.h"

BonusManager::BonusManager() {
    time_wait = 8000;
    time_start = SDL_GetTicks64();
}

BonusManager::~BonusManager() {
    clean_up();
}

Bonus* BonusManager::make_bonus(int bonus_type) {
    Bonus* bonus = NULL;
    switch(bonus_type) {
    case 0 :
        bonus = new Bonus("image\\heart_coin1.png", Vector2D(SCREEN_WIDTH, rand()%(GROUND_HEIGHT - 16)), 1, 1, Vector2D(-5, 0), 0);
        break;
    case 1:
        bonus = new Bonus("image\\bonus_score_coin1.png", Vector2D(SCREEN_WIDTH, rand()%(GROUND_HEIGHT - 16)), 1, 1, Vector2D(-5, 0), 1);
        break;
    case 2:
        bonus = new Bonus("image\\multi_arrow_coin1.png", Vector2D(SCREEN_WIDTH, rand()%(GROUND_HEIGHT - 16)), 1, 1, Vector2D(-5, 0), 2);
        break;
    case 3:
        bonus = new Bonus("image\\fire_arrow_coin1.png", Vector2D(SCREEN_WIDTH, rand()%(GROUND_HEIGHT - 16)), 1, 1, Vector2D(-5, 0), 3);
        break;
    default:
        break;
    }
    return bonus;
}

void BonusManager::init_bonus() {
    if ( SDL_GetTicks64() - time_start >= time_wait ) {
        int bonus_type = rand()%4;
        bonus_list.push_back(make_bonus(bonus_type));
        time_start = SDL_GetTicks64();
    }
}

void BonusManager::remove_bonus(const int& index) {
    if ( index < bonus_list.size() && index >= 0 ) {
        bonus_list.erase(bonus_list.begin() + index);
    }
}

void BonusManager::check_bonus() {
    for ( int i = 0; i < bonus_list.size(); ++i ) {
        if ( bonus_list[i]->get_xpos() < 0 ) bonus_list[i]->set_is_move(false);
        if ( !bonus_list[i]->get_is_move() ) remove_bonus(i);
    }
}

void BonusManager::update() {
    init_bonus();
    check_bonus();
    for ( int i = 0; i < bonus_list.size(); ++i ) {
        bonus_list[i]->update();
    }
}

void BonusManager::draw() {
    for ( int i = 0; i < bonus_list.size(); ++i ) {
        bonus_list[i]->draw();
    }
}

void BonusManager::clean_up() {
    bonus_list.clear();
}
