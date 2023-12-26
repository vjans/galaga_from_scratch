#ifndef ENEMY_H
#define ENEMY_H

#include "bgPlane.h"
#include "instance.h"
#include "graphicsUtils.h"
#include "bulletManager.h"

class Enemy{
public:
    BulletManager* bullet_manager;
	Instance en_instance;
	BGPlane* background;
	bool exists = false;
	float speed = 0.01;
	int shoot_delay = 5; // shoot each 40 frames
	int shoot_delay_counter = 0;
	
	Enemy();
	
	Enemy(BulletManager* bulletManager, BGPlane* background, Instance enemy_instance);
	void draw();
	void shoot();
	void animate(float time);
	void check_collision();
	
};
#endif
