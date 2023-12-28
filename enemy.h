#ifndef ENEMY_H
#define ENEMY_H

#include "bgPlane.h"
#include "instance.h"
#include "graphicsUtils.h"
#include "bulletManager.h"
#include "gameConstants.h"

class EnemyInfo{
public:
	BulletType bullet_type;
	AnimationType idle_animation;
	AnimationType movement_animation;
	AnimationType attack_animation;
	ModelType instance_model;
	DrawType draw_type;
	AIType ai_type;
	float health;
	float speed;
	float size;
	
	EnemyInfo(){}
	EnemyInfo(BulletType bt, AnimationType idl,AnimationType mvm,AnimationType atk,ModelType ins,DrawType dt,AIType ai,float h,float sp,float sz)
	: bullet_type(bt), idle_animation(idl), movement_animation(mvm), attack_animation(atk), instance_model(ins), draw_type(dt), ai_type(ai), health(h), speed(sp), size(sz){}
};

class Enemy{
public:
    BulletManager* bullet_manager;
	Instance en_instance;
	BGPlane* background;
	BulletType bullet_type = SINGLE_SHOT;
	EnemyState current_state = MOVE_ORIGIN; // when enemies spawn they should move to the origin point
	AIType ai_type;
	v2 origin;
	v2 target;
	v2 player_pos;
	bool exists = false;
	float speed = 0.01;
	float health = 1;
	float size = 1;
	int shoot_delay = 5; // shoot each 40 frames
	int shoot_delay_counter = 0;
	
	Enemy();
	
	//Enemy(BulletManager* bulletManager, BGPlane* background, Instance enemy_instance, float size = 1, float health = 1, WeaponType weapon_type = SINGLE_SHOT);
	Enemy(BulletManager* bullet_manager, BGPlane* background,  v2 pos, EnemyType en_type);
	void draw();
	void shoot();
	void animate(float time);
	void check_collision();
	
	void update_state_machine();
	void move_to_origin();
	void move_to_player();
	void idle();
	void wander();
	
	void set_animation_state(EnemyAnimationState animation_state);
	
	void update_player_pos(v2 pos);
};

EnemyInfo get_enemy_info_from_type(EnemyType enemy_type);
#endif
