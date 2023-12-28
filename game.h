#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "bgPlane.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletManager.h"
#include "gameConstants.h"
#include "textUtils.h"
class Game; // Forward declaration
struct MenuItem {
    std::string label;
    void (Game::*action)(); // Pointer to member function of Game
};

class Game {
public:
    Game();
    void run();
	
	BGPlane background;
    Player player;
    Enemy enemies[ENEMY_BUFFER_MAX];
    BulletManager bullet_manager;
    GameState current_state = MAIN_MENU;
    
    int current_level = 1;
    int max_level = 10;
    bool no_enemies_remain = true;
	  
	std::vector<MenuItem> main_menu_items;
	int selected_item_index = 0;
    
	float time;
	bool keys_pressed[5] = {false}; // Left, right, up, down, space
	
    void init_game();
    void load_enemies_for_current_level();
    
	void handle_player();
    void handle_enemies();
    void handle_bullets();
    
    void handle_entities();
    void draw_entities();
    
    void handle_main_menu();
    void start_game();
    void exit_game();
    
    void handle_pause_menu();
    void handle_shop_menu();
    void handle_game_over_screen();
    
	void update_key_presses(); // Method to update keys_pressed from external inputs
    void increment_time();
};


#endif // GAME_H
