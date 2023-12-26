#include "Game.h"
#include <cstdlib> // If you're using random numbers (for Enemy shooting logic)

Game::Game() {
    init_game();
}

void Game::init_game() {
    // Initialize the BulletManager
    for (int i = 0; i < BULLET_BUFFER_MAX; i++) {
        bullet_manager.bullets[i].exists = false;
    }
	background.init();
    // Initialize the Player
    Instance player_instance = Instance({0,-0.8},0.1, get_model_from_type(4), DEFAULT_PLAYER_INSTANCE);
    player = Player(&bullet_manager,&background,player_instance);

    // Initialize Enemies
    int encount = 10;
    for(int i = 0; i < ENEMY_BUFFER_MAX; i++) {
        if(!enemies[i].exists) {

            v2 v;
            v.x = ((float)i / 10.0f) - 0.5f;
            v.y = 0.7f;
            Instance inst = Instance(v,0.05,get_model_from_type(0), DEFAULT_ENEMY_INSTANCE);
            
            enemies[i] = Enemy(&bullet_manager,&background, inst);
			enemies[i].en_instance = inst;
            enemies[i].exists = true;
            encount--;
        }
        if(encount == 0) break;
    }
}

void Game::run() {
	background.draw(time);
    update_key_presses();
    handle_player();
    handle_bullets();
    handle_enemies();
    increment_time();
}

void Game::update_key_presses() {
    // Update the keys_pressed array based on your input handling logic
    // Then, update the player's key state
    for (int i = 0; i < 5; i++) {
        player.keys_pressed[i] = keys_pressed[i];
    }
}

void Game::handle_player() {
    player.move();
    player.shoot();
    player.check_collision();
    player.draw();
    player.animate(time);
}

void Game::handle_enemies() {
    for(int i = 0; i < ENEMY_BUFFER_MAX; i++) {
        if(enemies[i].exists) {
            enemies[i].draw();
            enemies[i].shoot();
            enemies[i].animate(time);
            enemies[i].check_collision();
        }
    }
}

void Game::handle_bullets() {
    bullet_manager.move_bullets();
    bullet_manager.animate_bullets(time);
    bullet_manager.draw_bullets();
}

void Game::increment_time(){
	time+=1;
}
