#ifndef PLAYER_H
#define PLAYER_H

#include "bgPlane.h"
#include "Instance.h" 
#include "graphicsUtils.h"
#include "BulletManager.h"

class Player {
public:
    BulletManager* bullet_manager;
    BGPlane* background; //for lighting
    Instance pl_instance;
    bool keys_pressed[5]; // Left, right, up, down, space
    bool moving_left = false;
    bool moving_right = false;
    float total_rotation = 0;
    float speed;
    int shoot_delay;
    int shoot_delay_counter;
	Player();
    Player(BulletManager* bulletManager, BGPlane* background, Instance player_instance);
    void move();
    void draw();
    void shoot();
    void animate(float time);
    void check_collision();
};

#endif // PLAYER_H
