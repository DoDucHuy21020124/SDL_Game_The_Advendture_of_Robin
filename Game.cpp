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
    play_time = 3;
    score = 0;
}

void Game::character_collision() {
    if ( !character->get_is_destroyed() ) {
        if ( check_collision(character->get_destRect(), dragon->get_destRect()) ) {
            --play_time;
            character->set_is_destroyed(true);
        }
    }
    if ( !character->get_is_destroyed() ) {
        for ( int i = 0; i < dragon->get_weapon().size(); ++i ) {
            if ( check_collision(dragon->get_weapon()[i]->get_destRect(), character->get_destRect()) && dragon->get_weapon()[i]->get_is_move() && !character->get_is_destroyed() ) {
                --play_time;
                dragon->get_weapon()[i]->set_is_move(false);
                character->set_is_destroyed(true);
            }
        }
    }
    if ( !character->get_is_destroyed() ) {
        for ( int i = 0; i < goat->get_weapon().size(); ++i ) {
            if (check_collision(goat->get_weapon()[i]->get_destRect(), character->get_destRect()) && goat->get_weapon()[i]->get_is_move() && !character->get_is_destroyed()) {
                --play_time;
                goat->get_weapon()[i]->set_is_move(false);
                character->set_is_destroyed(true);
                break;
            }
        }
    }
    if ( !character->get_is_destroyed() ) {
        for ( int i = 0; i < enemy_list->get_enemy_list().size(); ++i ) {
            if ( check_collision(enemy_list->get_enemy_list()[i]->get_destRect(), character->get_destRect()) && !enemy_list->get_enemy_list()[i]->get_is_destroying() && !enemy_list->get_enemy_list()[i]->get_is_destroyed() ) {
                --play_time;
                character->set_is_destroyed(true);
                break;
            }
        }
    }

}

void Game::destroy_enemy() {
    for ( int i = 0; i < character->get_weapon().size(); ++i ) {
        for ( int j = 0; j < enemy_list->get_enemy_list().size(); ++j ) {
            if ( check_collision(character->get_weapon()[i]->get_destRect(), enemy_list->get_enemy_list()[j]->get_destRect()) && !enemy_list->get_enemy_list()[j]->get_is_destroying()) {
                character->get_weapon()[i]->set_is_move(false);
                enemy_list->get_enemy_list()[j]->set_hp(enemy_list->get_enemy_list()[j]->get_hp() - character->get_weapon()[i]->get_damage() );
                if (enemy_list->get_enemy_list()[j]->get_hp() <= 0 ) {
                    enemy_list->get_enemy_list()[j]->set_is_destroying(true);
                    enemy_list->get_enemy_list()[j]->set_velocity(Vector2D(0, 0));
                    int x = enemy_list->get_enemy_list()[j]->get_xpos();
                    int y = enemy_list->get_enemy_list()[j]->get_ypos();
                    enemy_list->get_enemy_list()[j]->get_collision_effect()->set_xypos(Vector2D(float(x), float(y)));
                    score += enemy_list->get_enemy_list()[j]->get_score();
                    std::cout << score << std::endl;
                }
            }
                /*if ( enemys[j]->get_is_destroying() ) {
                    if ( weapon[i]->get_frame() >= weapon[i]->get_num_frame() ) {
                        enemys[j]->set_is_destroying(false);
                        enemys[j]->set_is_destroyed(true);
                        weapon[i]->set_is_move(false);
                    }
                    else {
                        weapon[i]->
                    }
                }*/
        }
    }
}

void Game::reset_game() {
    character->get_collision_effect()->set_frame(0);
    character->set_is_destroyed(false);
    character->set_xypos(Vector2D(SCREEN_WIDTH/2, GROUND_HEIGHT - 100));

    goat->clear_up();
    goat->set_xpos(-goat->get_destRect().w);
    goat->set_is_appear(false);
    goat->set_is_attacking(false);
    dragon->clear_up();
    dragon->set_frame(0);
    enemy_list->clear_up();
    enemy_list->set_time_start_bat(SDL_GetTicks64());
    enemy_list->set_time_start_wolf(SDL_GetTicks64());
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
    if ( character->get_is_destroyed() ) {
        character->get_collision_effect()->set_xypos(Vector2D(character->get_xpos() + 15, character->get_ypos() + 20));
        do {
            SDL_RenderClear(renderer);

            map_game1->draw();
            map_game2->draw();

            goat->draw();
            dragon->draw(SDL_FLIP_HORIZONTAL);
            enemy_list->draw();
            character->draw();
            character->play_collision_effect();

            SDL_RenderPresent(renderer);
        } while ( character->get_collision_effect()->get_frame() < character->get_collision_effect()->get_num_frame() - 1);
        SDL_Delay(1000);

        if ( play_time <= 0 ) {
            game_over = true;
            is_running = false;
        }

        else {
            reset_game();
        }

    }
    else {
        map_game1->draw();
        map_game2->draw();

        goat->draw();
        dragon->draw(SDL_FLIP_HORIZONTAL);
        enemy_list->draw();
        character->draw();
    }
}

void Game::clean_game() {
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Clean the game!" << std::endl;
}



