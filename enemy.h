#ifndef ENEMY_H
#define ENEMY_H

#include "bgPlane.h"
#include "instance.h"
#include "graphicsUtils.h"
#include "bulletManager.h"
#include "gameConstants.h"

class Enemy{
public:
    BulletManager* bullet_manager;
	Instance en_instance;
	BGPlane* background;
	bool exists = false;
	float speed = 0.01;
	float health = 1;
	float size = 1;
	int shoot_delay = 5; // shoot each 40 frames
	int shoot_delay_counter = 0;
	
	Enemy();
	
	//Enemy(BulletManager* bulletManager, BGPlane* background, Instance enemy_instance, float size = 1, float health = 1, WeaponType weapon_type = SINGLE_SHOT);
	Enemy(BulletManager* bullet_manager, BGPlane* background,  v2 pos, InstanceType enemy_type);
	void draw();
	void shoot();
	void animate(float time);
	void check_collision();
	
};
#endif
