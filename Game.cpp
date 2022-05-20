#include <iostream>
#include <fstream>
#include "Game.h"
#include "Vector2D.h"

SDL_Renderer* Game::renderer;
Map* Game::map_game1;
Map* Game::map_game2;
SDL_Event Game::g_event;

int Game::score;
int Game::check_point;


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

        std::fstream file("data\\high_score.txt");
        if ( file.is_open() ) file >> high_score;
        file.close();

        is_running = true;
        game_over = false;
    }
}

int Game::make_menu() {
    TextureManager* menu_background = new TextureManager("image\\menu_background.png", Vector2D(0, 0), 1, 1);
    std::string title1 = "The Adventure";
    TextManager game_title1(title1, SDL_Color{255, 255, 255}, "font\\chary.ttf", 100, Vector2D(300, 100));
    std::string title2 = "of Robin";
    TextManager game_title2(title2, SDL_Color{255, 255, 255}, "font\\chary.ttf", 100, Vector2D(600, 200));

    TextureManager* deco = new TextureManager("image\\bat.png", Vector2D(550, 300), 4, 80);

    std::vector<TextureManager*> buttons;
    std::vector<bool> isSelected;

    TextureManager* play_button = new TextureManager("image\\play_button1.png", Vector2D(400, 400), 1, 1);
    buttons.push_back(play_button);

    TextureManager* high_score = new TextureManager("image\\high_score_button1.png", Vector2D(480, 400), 1, 1);
    buttons.push_back(high_score);

    TextureManager* info_button = new TextureManager("image\\info_button1.png", Vector2D(560, 400), 1, 1);
    buttons.push_back(info_button);

    TextureManager* quit_button = new TextureManager("image\\quit_button1.png", Vector2D(640, 400), 1, 1);
    buttons.push_back(quit_button);

    for ( int i = 0; i < buttons.size(); ++i ) isSelected.push_back(false);

    do {


        SDL_RenderClear(renderer);
        while ( SDL_PollEvent(&g_event) ) {
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
                        buttons[1]->set_file_path("image\\high_score_button.png", 1);
                    }
                }
                else if ( isSelected[1] ) {
                    isSelected[1] = false;
                    buttons[1]->set_file_path("image\\high_score_button1.png", 1);
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
                        buttons.clear();
                        return i;
                    }
                }
                break;
            default:
                break;
            }
        }

        deco->update();

        menu_background->draw();
        game_title1.draw();
        game_title2.draw();

        deco->draw();

        for ( int i = 0; i < buttons.size(); ++i ) {
            buttons[i]->update();
            buttons[i]->draw();
        }

        SDL_RenderPresent(renderer);
    } while ( true );
    return 3;
}

void Game::make_high_score() {
    TextureManager* menu_background = new TextureManager("image\\menu_background.png", Vector2D(0, 0), 1, 1);
    TextureManager* high_score_background = new TextureManager("image\\high_scorebackground.png", Vector2D(400, 50), 1, 1);

    TextManager* text = new TextManager("HIGH SCORE", SDL_Color{0, 0, 0}, "font\\chary.ttf", 50, Vector2D(470, 100));
    TextManager* highscore = new TextManager(std::to_string(high_score), SDL_Color{0, 0, 0}, "font\\chary.ttf", 50, Vector2D(550, 200));

    TextureManager* back_button = new TextureManager("image\\back_button1.png", Vector2D(1100, 536), 1, 1);
    TextureManager* reset_button = new TextureManager("image\\reset_button1.png", Vector2D(520, 350), 1, 1);
    bool check1 = false;
    bool check2 = false;
    bool quit = false;

    do {
        SDL_RenderClear(renderer);

        while( SDL_PollEvent(&g_event) ) {
            switch(g_event.type) {
            case SDL_QUIT :
                clean_game();
                break;
            case SDL_MOUSEMOTION :
                if ( check_in_button(g_event.motion.x, g_event.motion.y, back_button->get_destRect()) ) {
                    if ( !check1 ) {
                        check1 = true;
                        back_button->set_file_path("image\\back_button.png", 1);
                    }
                }
                else if ( check1 ) {
                    check1 = false;
                    back_button->set_file_path("image\\back_button1.png", 1);
                }

                if ( check_in_button(g_event.motion.x, g_event.motion.y, reset_button->get_destRect()) ) {
                    if ( !check2 ) {
                        check2 = true;
                        reset_button->set_file_path("image\\reset_button.png", 1);
                    }
                }
                else if ( check2 ) {
                    check2 = false;
                    reset_button->set_file_path("image\\reset_button1.png", 1);
                }
                break;
            case SDL_MOUSEBUTTONDOWN :
                if ( check_in_button(g_event.button.x, g_event.button.y, back_button->get_destRect()) ) {
                    quit = true;
                }

                if ( check_in_button(g_event.button.x, g_event.button.y, reset_button->get_destRect()) ) {
                    high_score = 0;
                    std::fstream file("data\\high_score.txt", std::ios::out | std::ios::trunc);
                    file << high_score;
                    file.close();
                    highscore->set_text(std::to_string(high_score));
                }
                break;
            }
        }

        highscore->update();

        menu_background->draw();
        high_score_background->draw();
        text->draw();
        highscore->draw();
        reset_button->draw();
        back_button->draw();

        SDL_RenderPresent(renderer);

    } while ( !quit );
}

void Game::make_info_game() {
    TextureManager* menu_background = new TextureManager("image\\menu_background.png", Vector2D(0, 0), 1, 1);
    TextureManager* info_background = new TextureManager("image\\info_background.png", Vector2D(200, 30), 1, 1);

    TextManager* text1 = new TextManager("This game was made by", SDL_Color{0, 0, 0}, "font\\chary.ttf", 50, Vector2D(350, 150));
    TextManager* text2 = new TextManager("Do Duc Huy", SDL_Color{0, 0, 0}, "font\\chary.ttf", 50, Vector2D(470, 250));
    TextManager* text3 = new TextManager("Student ID: 21020124", SDL_Color{0, 0, 0}, "font\\chary.ttf", 50, Vector2D(350, 350));

    TextureManager* back_button = new TextureManager("image\\back_button1.png", Vector2D(1100, 536), 1, 1);
    bool check = false;
    bool quit = false;

    do {
        SDL_RenderClear(renderer);

        while( SDL_PollEvent(&g_event) ) {
            switch(g_event.type) {
            case SDL_QUIT :
                clean_game();
                break;
            case SDL_MOUSEMOTION :
                if ( check_in_button(g_event.motion.x, g_event.motion.y, back_button->get_destRect()) ) {
                    if ( !check ) {
                        check = true;
                        back_button->set_file_path("image\\back_button.png", 1);
                    }
                }
                else if ( check ) {
                    check = false;
                    back_button->set_file_path("image\\back_button1.png", 1);
                }
                break;
            case SDL_MOUSEBUTTONDOWN :
                if ( check_in_button(g_event.button.x, g_event.button.y, back_button->get_destRect()) ) {
                    quit = true;
                }
                break;
            }
        }

        menu_background->draw();
        info_background->draw();
        text1->draw();
        text2->draw();
        text3->draw();

        back_button->draw();

        SDL_RenderPresent(renderer);

    } while ( !quit );

}

int Game::make_play_again() {
    TextureManager* gameover_background = new TextureManager("image\\gameover_background.png", Vector2D(0, 0), 1, 1);

    TextManager* score_text = NULL;

    if ( score > high_score ) {
        score_text = new TextManager("HIGH SCORE: " + std::to_string(score), SDL_Color{255, 255, 255}, "font\\chary.ttf", 50, Vector2D(450, 20));
        high_score = score;
        std::fstream file("data\\high_score.txt");
        file << high_score;
        file.close();
    }

    else {
        score_text = new TextManager("SCORE: " + std::to_string(score), SDL_Color{255, 255, 255}, "font\\chary.ttf", 50, Vector2D(500, 20));
    }

    TextManager* text1 = new TextManager("GAME OVER!", SDL_Color{255, 255, 255}, "font\\chary.ttf", 100, Vector2D(400, 250));
    TextManager* text2 = new TextManager("Do you want to play again?", SDL_Color{255, 255, 255}, "font\\chary.ttf", 50, Vector2D(350, 350));

    std::vector<TextureManager*> buttons;

    TextureManager* yes_button = new TextureManager("image\\yes_button.png", Vector2D(420, 420), 1, 1);
    buttons.push_back(yes_button);
    TextureManager* no_button = new TextureManager("image\\no_button.png", Vector2D(720, 420), 1, 1);
    buttons.push_back(no_button);

    std::vector<bool> check;
    for ( int i = 0; i < buttons.size(); ++i ) check.push_back(false);

    do {
        SDL_RenderClear(renderer);

        while( SDL_PollEvent(&g_event) ) {
            switch(g_event.type) {
            case SDL_QUIT :
                clean_game();
                exit(0);
                break;
            case SDL_MOUSEMOTION :
                if ( check_in_button(g_event.motion.x, g_event.motion.y, buttons[0]->get_destRect()) ) {
                    if ( !check[0] ) {
                        check[0] = true;
                        buttons[0]->set_file_path("image\\yes_button1.png", 1);
                    }
                }
                else if ( check[0] ) {
                    check[0] = false;
                    buttons[0]->set_file_path("image\\yes_button.png", 1);
                }

                if ( check_in_button(g_event.motion.x, g_event.motion.y, buttons[1]->get_destRect()) ) {
                    if ( !check[1] ) {
                        check[1] = true;
                        buttons[1]->set_file_path("image\\no_button1.png", 1);
                    }
                }
                else if ( check[1] ) {
                    check[1] = false;
                    buttons[1]->set_file_path("image\\no_button.png", 1);
                }
                break;
            case SDL_MOUSEBUTTONDOWN :
                for ( int i = 0; i < buttons.size(); ++i ) {
                    if ( check_in_button(g_event.button.x, g_event.button.y, buttons[i]->get_destRect()) ) {
                        return i;
                    }
                }
                break;
            }
        }

        gameover_background->draw();

        score_text->draw();

        text1->draw();
        text2->draw();

        yes_button->draw();
        no_button->draw();

        SDL_RenderPresent(renderer);

    } while ( true );
    return 1;

}

void Game::handle_event() {
    SDL_PollEvent(&g_event);
    if ( g_event.type == SDL_QUIT ) {
        game_over = true;
        is_running = false;
        clean_game();
        exit(0);
    }
    else if ( g_event.type == SDL_KEYDOWN ) {
        if ( g_event.key.keysym.sym == SDLK_ESCAPE ) {
            pause_game = true;
        }
        else if ( g_event.key.keysym.sym == SDLK_SPACE ) {
            if ( pause_game ) pause_game = false;
        }
    }
    else if ( g_event.type == SDL_WINDOWEVENT_MINIMIZED ) {
        SDL_MinimizeWindow(window);
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
    check_point = 0;

    show_hp = new TextManager("x" + std::to_string(play_time), SDL_Color{255, 255, 255}, "font\\FVF Fernando 08.ttf", 15, Vector2D(50, 2) );
    show_score = new TextManager("Score: " + std::to_string(score), SDL_Color{255, 255, 255}, "font\\FVF Fernando 08.ttf", 15, Vector2D(SCREEN_WIDTH/2 - 50, 2));
    heart = new TextureManager("image\\heart.png", Vector2D(20, 4), 1, 1);

    pause_game = false;
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
    if ( !pause_game ) {
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

        if ( score - check_point > 50 ) {
            enemy_list->set_time_appear_bat(enemy_list->get_time_appear_bat() - 500);
            if ( enemy_list->get_time_appear_bat() < 3000 ) enemy_list->set_time_appear_bat(3000);

            enemy_list->set_time_appear_wolf(enemy_list->get_time_appear_wolf() - 500);
            if ( enemy_list->get_time_appear_wolf() < 7000 ) enemy_list->set_time_appear_bat(7000);

            bonus_list->set_time_wait(bonus_list->get_time_wait() + 1000);
            if ( bonus_list->get_time_wait() > 20000 ) bonus_list->set_time_wait(20000);

            check_point += 50;
        }
    }
    else {
        pause_text->update();
    }
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
    if ( pause_game ) {
        pause_text->draw();
    }
}

void Game::clean_game() {
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
}



