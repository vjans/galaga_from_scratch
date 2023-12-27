#include "Game.h"
#include <cstdlib> 

Game::Game() {
    //init_game();
}

void Game::init_game() {
    // Initialize the BulletManager
    for (int i = 0; i < BULLET_BUFFER_MAX; i++) {
        bullet_manager.bullets[i].exists = false;
    }
	background.init();
    // Initialize the Player
    Instance player_instance = Instance({0,-0.8},0.1, get_model_from_type(PLAYER_MODEL1), DEFAULT_PLAYER_INSTANCE);
    player = Player(&bullet_manager,&background,player_instance);

    // Initialize Enemies
    int encount = 10;
    for(int i = 0; i < ENEMY_BUFFER_MAX; i++) {
        if(!enemies[i].exists) {

            v2 v;
            v.x = ((float)i / 10.0f) - 0.5f;
            v.y = 0.7f;
            Instance inst = Instance(v,0.05,get_model_from_type(ENEMY_DOUBLE_OCT), DEFAULT_ENEMY_INSTANCE);
            
            enemies[i] = Enemy(&bullet_manager,&background, inst);
			enemies[i].en_instance = inst;
            enemies[i].exists = true;
            encount--;
        }
        if(encount == 0) break;
    }
    
    // init main menu
    
    main_menu_items.push_back({"Start", &Game::start_game});
    main_menu_items.push_back({"Exit", &Game::exit_game});
    
}

void Game::start_game() {
    current_state = PLAYING;
}

void Game::exit_game() {
    exit(0);
}

/*


enum GameState{
    MAIN_MENU,
    PLAYING, // while inside of a level
    PLAYING_SHOP, // shopping interface between levels
    PAUSED,
    GAME_OVER
};
*/

void Game::run() {
	background.draw(time);
	switch(current_state){
		case MAIN_MENU: 
			handle_main_menu();
		break;
		case PLAYING: 
		    update_key_presses();
		    handle_entities();
		    draw_entities();
			increment_time();
		break;
		case PLAYING_SHOP: 
			handle_shop_menu();
		    draw_entities();
			
		break;
		case PAUSED: 
			handle_pause_menu();
		    draw_entities();
			
		break;
		case GAME_OVER: 
			handle_game_over_screen();
		break;
		}
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
}

void Game::handle_enemies() {
    for(int i = 0; i < ENEMY_BUFFER_MAX; i++) {
        if(enemies[i].exists) {
            enemies[i].shoot();
            enemies[i].check_collision();
        }
    }
}

void Game::handle_bullets() {
    bullet_manager.move_bullets();
}

void Game::handle_entities(){
	handle_player();
    handle_bullets();
    handle_enemies();
}

void Game::draw_entities(){
	
    player.draw();
    player.animate(time);
    
    bullet_manager.animate_bullets(time);
    bullet_manager.draw_bullets();
    
    for(int i = 0; i < ENEMY_BUFFER_MAX; i++) {
    if(enemies[i].exists) {
            enemies[i].draw();
            enemies[i].animate(time);
        }
    }
}

void Game::handle_main_menu() {
    // Render menu items
    for (size_t i = 0; i < main_menu_items.size(); ++i) {
        if (i == selected_item_index) {
            // Highlight the selected item
            write_text(main_menu_items[i].label, {0, 0 - 0.1f * i, 0}, 0.01, {1, 0, 0});
        } else {
            write_text(main_menu_items[i].label, {0, 0 - 0.1f * i, 0}, 0.01, {1, 1, 1});
        }
    }

	if(keys_pressed[2]){
		selected_item_index--;
		if(selected_item_index < 0){
			selected_item_index = 0;
		}
	}
	if(keys_pressed[3]){
		selected_item_index++;
		if(selected_item_index > main_menu_items.size()-1){
			selected_item_index = main_menu_items.size()-1;
		}
	}
    // If Enter is pressed, execute the action of the selected item
    if (keys_pressed[4]) {
        (this->*main_menu_items[selected_item_index].action)();
    }
}


void Game::handle_pause_menu(){
	current_state = PLAYING;
}
void Game::handle_shop_menu(){
	current_state = PLAYING;
}
void Game::handle_game_over_screen(){
	current_state = MAIN_MENU;
}

void Game::increment_time(){
	time+=1;
}
