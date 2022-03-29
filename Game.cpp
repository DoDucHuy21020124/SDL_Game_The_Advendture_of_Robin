#include <iostream>
#include "Game.h"
#include "Vector2D.h"

SDL_Renderer* Game::renderer;
Map* Game::map_game1;
Map* Game::map_game2;
SDL_Event Game::g_event;

Character* Game::character;
Wolf* Game::wolf;
Dragon* Game::dragon;
Bat* Game::bat;


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
    map_game1 = new Map("image\\backgroundgame.png", Vector2D(0, 0), 1);
    map_game2 = new Map("image\\backgroundgame.png", Vector2D(SCREEN_WIDTH, 0), 1);

    character = new Character("image\\archer_walk.png", Vector2D(SCREEN_WIDTH/2, GROUND_HEIGHT - 100), 8, Vector2D(10, 25));

    dragon = new Dragon("image\\dragon.png", Vector2D(-300, GROUND_HEIGHT - 512), 32, Vector2D(0, 0));
    wolf = new Wolf("image\\wolf.png", Vector2D(SCREEN_WIDTH, GROUND_HEIGHT - 64), 8, Vector2D(-8, 0));
    bat = new Bat("image\\bat.png", Vector2D(SCREEN_WIDTH, 200), 4, Vector2D(-5, 2));
}

void Game::update_game() {
    map_game1->update();
    map_game2->update();

    character->update();
    dragon->update();
    wolf->update();
    bat->update();
}

void Game::render_game() {
    map_game1->draw();
    map_game2->draw();

    character->draw();
    dragon->draw(SDL_FLIP_HORIZONTAL);
    wolf->draw();
    bat->draw();
}

void Game::clean_game() {
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Clean the game!" << std::endl;
}



