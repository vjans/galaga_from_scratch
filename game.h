#ifndef GAME_H
#define GAME_H

#include "bgPlane.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletManager.h"
#include "gameConstants.h"


class Game {
public:
    Game();
    void run();
	
	BGPlane background;
    Player player;
    Enemy enemies[ENEMY_BUFFER_MAX];
    BulletManager bullet_manager;
    float time;
	bool keys_pressed[5] = {false}; // Left, right, up, down, space
	
    void init_game();
    void handle_player();
    void handle_enemies();
    void handle_bullets();
    void update_key_presses(); // Method to update keys_pressed from external inputs
    void increment_time();
};

#endif // GAME_H
