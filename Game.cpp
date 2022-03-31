#include <iostream>
#include "Game.h"
#include "Vector2D.h"

SDL_Renderer* Game::renderer;
Map* Game::map_game1;
Map* Game::map_game2;
SDL_Event Game::g_event;

int Game::score;

Character* Game::character;
Goat* Game::goat;
Dragon* Game::dragon;
EnemyManager* Game::enemy_list;

void Game::game_init() {
    if ( SDL_Init(SDL_INIT_EVERYTHING) == 0 ) {
        std::cout << "Init Successful" << std::endl;
        window = SDL_CreateWindow("The Adventure of Robin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if ( window ) {
            std::cout << "Create Window Successful!" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer ) {
            std::cout << "Create Renderer Successful!" << std::endl;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0) {
            std::cout << "Create Mixer Successful" << std::endl;
        }

        if ( TTF_Init() == 0 ) {
            std::cout << "Create TTF Successful" << std::endl;
        }

        is_running = true;
        game_over = false;
    }
}

void Game::handle_event() {
    SDL_PollEvent(&g_event);
    if ( g_event.type == SDL_QUIT ) {
        game_over = true;
        is_running = false;
    }
}

void Game::setup_game() {
    map_game1 = new Map("image\\backgroundgame.png", Vector2D(0, 0), 1, 1);
    map_game2 = new Map("image\\backgroundgame.png", Vector2D(SCREEN_WIDTH, 0), 1, 1);

    character = new Character("image\\archer_walk.png", Vector2D(SCREEN_WIDTH/2, GROUND_HEIGHT - 100), 8, 80, Vector2D(10, 25));

    goat = new Goat("image\\goat.png", Vector2D(0, GROUND_HEIGHT - 450), 4, 150, Vector2D(5, 0));
    dragon = new Dragon("image\\dragon.png", Vector2D(-300, GROUND_HEIGHT - 512), 32, 100, Vector2D(0, 0));
    enemy_list = new EnemyManager();

    time_start = SDL_GetTicks64();
    play_time = 1;
    score = 0;
}

void Game::character_collision() {
    if ( check_collision(character->get_destRect(), dragon->get_destRect()) ) {
        --play_time;
    }
    for ( int i = 0; i < dragon->get_weapon().size(); ++i ) {
        if ( check_collision(dragon->get_weapon()[i]->get_destRect(), character->get_destRect()) ) {
            --play_time;
        }
    }
    for ( int i = 0; i < goat->get_weapon().size(); ++i ) {
        if (check_collision(goat->get_weapon()[i]->get_destRect(), character->get_destRect())) {
            --play_time;
            break;
        }
    }
    for ( int i = 0; i < enemy_list->get_enemy_list().size(); ++i ) {
        if ( check_collision(enemy_list->get_enemy_list()[i]->get_destRect(), character->get_destRect())) {
            --play_time;
            break;
        }
    }
    if ( play_time <= 0 ) {
        game_over = true;
        is_running = false;
    }
}

void Game::destroy_enemy() {
    for ( int i = 0; i < character->get_weapon().size(); ++i ) {
        for ( int j = 0; j < enemy_list->get_enemy_list().size(); ++j ) {
            if ( check_collision(character->get_weapon()[i]->get_destRect(), enemy_list->get_enemy_list()[j]->get_destRect() )) {
                enemy_list->get_enemy_list()[j]->set_is_destroyed(true);
                character->get_weapon()[i]->set_is_move(false);
                score += enemy_list->get_enemy_list()[j]->get_hp();
                std::cout << score << std::endl;
            }
        }
    }
}

void Game::update_game() {
    map_game1->update();
    map_game2->update();

    character_collision();
    destroy_enemy();

    character->update();
    goat->attack(character->get_xpos());
    goat->update();
    dragon->update();

    enemy_list->init_enemy_bat(character->get_xpos(), character->get_ypos());
    enemy_list->init_enemy_wolf();
    enemy_list->update();
}

void Game::render_game() {
    map_game1->draw();
    map_game2->draw();

    goat->draw();
    dragon->draw(SDL_FLIP_HORIZONTAL);
    enemy_list->draw();
    character->draw();
}

void Game::clean_game() {
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Clean the game!" << std::endl;
}



