#include <iostream>
#include <fstream>
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
BonusManager* Game::bonus_list;

TextManager* Game::show_score;
TextManager* Game::show_time;
TextManager* Game::show_hp;
TextureManager* Game::heart;

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

        fstream file("data\\high_score.txt");
        if ( file.is_open() ) file >> high_score;
        file.close();

        is_running = true;
        game_over = false;
    }
}

int Game::make_menu() {
    TextureManager* menu_background = new TextureManager("image\\menu_background.png", Vector2D(0, 0), 1, 1);
    std::cout << "Load menu_background" << std::endl;

    std::string title = "The Adventure\n";
    title = title + "      of Robin";
    TextManager game_title(title, SDL_Color{0, 0, 0}, "font\\FlappyBirdy.ttf", 100, Vector2D(400, 200));
    std::cout << "load title" << std::endl;

    std::vector<TextureManager*> buttons;
    std::vector<bool> isSelected;

    TextureManager* play_button = new TextureManager("image\\play_button1.png", Vector2D(400, 400), 1, 1);
    buttons.push_back(play_button);
    std::cout << "start_button" << std::endl;

    TextureManager* high_score = new TextureManager("image\\high_score1.png", Vector2D(480, 400), 1, 1);
    std::cout << "Install" << std::endl;
    buttons.push_back(high_score);
    std::cout << "start_button" << std::endl;

    TextureManager* info_button = new TextureManager("image\\info_button1.png", Vector2D(560, 400), 1, 1);
    buttons.push_back(info_button);
    std::cout << "start_button" << std::endl;

    TextureManager* quit_button = new TextureManager("image\\quit_button1.png", Vector2D(640, 400), 1, 1);
    buttons.push_back(quit_button);
    std::cout << "start_button" << std::endl;

    for ( int i = 0; i < buttons.size(); ++i ) isSelected.push_back(false);

    std::cout << "Success install" << std::endl;

    do {
        SDL_RenderClear(renderer);
        std::cout << "Clear Render" << std::endl;

        while ( SDL_PollEvent(&g_event) ) {
            std::cout << "Wait event" << std::endl;
            switch (g_event.type) {
            case SDL_QUIT :
                return 3;
                break;
            case SDL_MOUSEMOTION:
                if ( check_in_button(g_event.motion.x, g_event.motion.y, buttons[0]->get_destRect()) ) {
                    if ( !isSelected[0] ) {
                        isSelected[0] = true;
                        buttons[0]->set_file_path("image\\play_button.png", 1);
                    }
                }
                else if ( isSelected[0] ) {
                    isSelected[0] = false;
                    buttons[0]->set_file_path("image\\play_button1.png", 1);
                }

                if ( check_in_button(g_event.motion.x, g_event.motion.y, buttons[1]->get_destRect()) ) {
                    if ( !isSelected[1] ) {
                        isSelected[1] = true;
                        buttons[1]->set_file_path("image\\high_score.png", 1);
                    }
                }
                else if ( isSelected[1] ) {
                    isSelected[1] = false;
                    buttons[1]->set_file_path("image\\high_score1.png", 1);
                }

                if ( check_in_button(g_event.motion.x, g_event.motion.y, buttons[2]->get_destRect()) ) {
                    if ( !isSelected[2] ) {
                        isSelected[2] = true;
                        buttons[2]->set_file_path("image\\info_button.png", 1);
                    }
                }
                else if ( isSelected[2] ) {
                    isSelected[2] = false;
                    buttons[2]->set_file_path("image\\info_button1.png", 1);
                }

                if ( check_in_button(g_event.motion.x, g_event.motion.y, buttons[3]->get_destRect()) ) {
                    if ( !isSelected[3] ) {
                        isSelected[3] = true;
                        buttons[3]->set_file_path("image\\quit_button.png", 1);
                    }
                }
                else if ( isSelected[3] ) {
                    isSelected[3] = false;
                    buttons[3]->set_file_path("image\\quit_button1.png", 1);
                }
                break;
            case SDL_MOUSEBUTTONDOWN :
                for ( int i = 0; i < buttons.size(); ++i ) {
                    if ( check_in_button(g_event.button.x, g_event.button.y, buttons[i]->get_destRect()) ) {
                        std::cout << "click" << std::endl;
                        buttons.clear();
                        std::cout << "button clear" << std::endl;
                        return i;
                    }
                }
                break;
            default:
                break;
            }
        }

        menu_background->draw();
        game_title.draw();

        for ( int i = 0; i < buttons.size(); ++i ) {
            buttons[i]->update();
            buttons[i]->draw();
        }

        SDL_RenderPresent(renderer);
    } while ( true );
    return 3;
}

void Game::make_high_score() {

}

void Game::make_info_game() {

}

int Game::make_play_again() {

}

void Game::handle_event() {
    SDL_PollEvent(&g_event);
    if ( g_event.type == SDL_QUIT ) {
        game_over = true;
        is_running = false;
    }
}

void Game::setup_game() {
    map_game1 = NULL;
    map_game2 = NULL;

    character = NULL;
    goat = NULL;
    dragon = NULL;
    enemy_list = NULL;
    bonus_list = NULL;
    show_hp = NULL;
    show_score = NULL;
    heart = NULL;

    map_game1 = new Map("image\\backgroundgame.png", Vector2D(0, 0), 1, 1);
    map_game2 = new Map("image\\backgroundgame.png", Vector2D(SCREEN_WIDTH, 0), 1, 1);

    character = new Character("image\\archer_walk.png", Vector2D(SCREEN_WIDTH/2, GROUND_HEIGHT - 100), 8, 80, Vector2D(10, 25));

    goat = new Goat("image\\goat.png", Vector2D(0, GROUND_HEIGHT - 450), 4, 150, Vector2D(5, 0));
    dragon = new Dragon("image\\dragon.png", Vector2D(-300, GROUND_HEIGHT - 512), 32, 100, Vector2D(0, 0));
    enemy_list = new EnemyManager();
    bonus_list = new BonusManager();

    time_start = SDL_GetTicks64();
    play_time = 3;
    score = 0;

    show_hp = new TextManager("x" + std::to_string(play_time), SDL_Color{255, 255, 255}, "font\\FVF Fernando 08.ttf", 15, Vector2D(50, 2) );
    show_score = new TextManager("Score: " + std::to_string(score), SDL_Color{255, 255, 255}, "font\\FVF Fernando 08.ttf", 15, Vector2D(SCREEN_WIDTH/2 - 50, 2));
    heart = new TextureManager("image\\heart.png", Vector2D(20, 4), 1, 1);
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
                play_sound_effect("music\\kill_enemy.wav");
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
        }
    }
}

void Game::take_bonus() {
    for ( int i = 0; i < bonus_list->get_bonus_list().size(); ++i ) {
        if ( check_collision(bonus_list->get_bonus_list()[i]->get_destRect(), character->get_destRect()) && bonus_list->get_bonus_list()[i]->get_is_move()) {
            play_sound_effect("music\\take_coin.wav");
            switch(bonus_list->get_bonus_list()[i]->get_bonus_type()) {
            case 0:
                ++play_time;
                break;
            case 1:
                score += 5;
                std::cout << score << std::endl;
                break;
            case 2:
                character->set_weapon_type(1);
                character->set_time_start(SDL_GetTicks64());
                break;
            case 3:
                character->set_weapon_type(2);
                character->set_time_start(SDL_GetTicks64());
                break;
            default :
                break;
            }
            bonus_list->get_bonus_list()[i]->set_is_move(false);
        }
    }
}

void Game::reset_game() {
    character->get_collision_effect()->set_frame(0);
    character->set_is_destroyed(false);
    character->set_xypos(Vector2D(SCREEN_WIDTH/2, GROUND_HEIGHT - 100));
    character->set_weapon_type(0);

    goat->clear_up();
    goat->set_xpos(-goat->get_destRect().w);
    goat->set_is_appear(false);
    goat->set_is_attacking(false);
    goat->set_num_attack(0);
    dragon->clear_up();
    dragon->set_frame(0);
    enemy_list->clear_up();
    enemy_list->set_time_start_bat(SDL_GetTicks64());
    enemy_list->set_time_start_wolf(SDL_GetTicks64());
}

void Game::update_game() {
    map_game1->update();
    map_game2->update();

    show_hp->set_text("x" + std::to_string(play_time));
    show_hp->update();

    show_score->set_text("Score: " + std::to_string(score));
    show_score->update();

    character_collision();
    destroy_enemy();
    take_bonus();

    character->update();
    goat->attack(character->get_xpos());
    goat->update();
    dragon->update();

    enemy_list->init_enemy_bat(character->get_xpos(), character->get_ypos());
    enemy_list->init_enemy_wolf();
    enemy_list->update();
    heart->update();

    bonus_list->init_bonus();
    bonus_list->update();
}

void Game::render_game() {
    if ( character->get_is_destroyed() ) {
        play_sound_effect("music\\main_die.wav");
        character->get_collision_effect()->set_xypos(Vector2D(character->get_xpos() + 15, character->get_ypos() + 20));
        do {
            SDL_RenderClear(renderer);

            map_game1->draw();
            map_game2->draw();

            show_hp->draw();
            show_score->draw();
            heart->draw();

            goat->draw();
            dragon->draw(SDL_FLIP_HORIZONTAL);
            bonus_list->draw();
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

        show_hp->draw();
        show_score->draw();
        heart->draw();

        goat->draw();
        dragon->draw(SDL_FLIP_HORIZONTAL);
        bonus_list->draw();
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



