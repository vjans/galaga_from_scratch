#include "enemy.h"
#include <cstdlib>


/*
AI_TRANSITIONS

class EnemyInfo{
	BulletType bullet_type;
	AnimationType idle_animation;
	AnimationType movement_animation;
	AnimationType attack_animation;
	ModelType instance_model;
};
*/



Enemy::Enemy() {}
Enemy::Enemy(BulletManager* bullet_manager, BGPlane* background,  v2 pos, EnemyType en_type) 
	: bullet_manager(bullet_manager), background(background), origin(pos) {
		
		EnemyInfo en_info = get_enemy_info_from_type(en_type);
		
		target = origin;
		
        bullet_type = en_info.bullet_type;
        size = en_info.size;
        speed = en_info.speed;
        health = en_info.health;
        
        
		en_instance = Instance({0,1},size,get_model_from_type(en_info.instance_model), en_info.draw_type);
        en_instance.add_animation(get_animation_from_type(en_info.idle_animation));
        en_instance.add_animation(get_animation_from_type(en_info.movement_animation));
        en_instance.add_animation(get_animation_from_type(en_info.attack_animation));
        set_animation_state(MOVING);
    exists = true;
}

void Enemy::draw() {
    en_instance.draw();
    
    // enemy light
    
    background->add_light(en_instance.pos, {1,1,1}, en_instance.size*1.2);
}
void Enemy::animate(float time){
	en_instance.animate(time);
}

void Enemy::shoot() {
    shoot_delay_counter--;
    if(shoot_delay_counter <= 0 && rand() % 100 == 0) {
        shoot_delay_counter = shoot_delay;
        v2 forward = {0.0, -0.01};
        bullet_manager->spawn_bullet(en_instance.pos, forward, HOSTILE, bullet_type);
    }
}

void Enemy::check_collision(){
	for(int i = 0; i < BULLET_BUFFER_MAX; i++){
		if(bullet_manager->bullets[i].exists && bullet_manager->bullets[i].alignment == FRIENDLY){
			bool collides = en_instance.check_collision(bullet_manager->bullets[i].instance);
			if(collides){
				
				health--;
				bullet_manager->bullets[i].exists = false;
				// some logic like damage and piercing can be added here
				if(health == 0){
					exists = false;
						
				}
			}
		}
	}
}


void Enemy::set_animation_state(EnemyAnimationState animation_state){
	en_instance.current_animation_index = static_cast<int>(animation_state);
}

void Enemy::update_state_machine(){
	switch(current_state){
	
	case IDLE_ORIGIN: idle(); break;
	case IDLE_SOMEWHERE: break;
	case DEFAULT_SHOOTING: break;
	case MOVE_ORIGIN: move_to_origin(); break;
	case MOVE_PLAYER: move_to_player();  break;
	case WANDER: wander(); break;
	}
}



void Enemy::move_to_origin() {
    // Calculate direction vector from current position to origin
    v2 direction = {origin.x - en_instance.pos.x, origin.y - en_instance.pos.y};

    // Normalize the direction vector
    float magnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	// Check if the enemy is close enough to the origin
    if (magnitude <= 0.02) {
        current_state = IDLE_ORIGIN; // Switch to IDLE_ORIGIN state
        set_animation_state(IDLE);
        return; // Stop further movement processing
    }		
    if (magnitude > 0) {
        direction.x /= magnitude;
        direction.y /= magnitude;
    }

    // Move towards the origin at the given speed
    en_instance.pos.x += direction.x * speed;
    en_instance.pos.y += direction.y * speed;

    // Optionally, you can add a condition to switch state once the origin is reached or within a certain threshold
}

void Enemy::move_to_player(){
// Calculate direction vector from current position to origin
    v2 direction = {player_pos.x - en_instance.pos.x, origin.y - player_pos.y};

    // Normalize the direction vector
    float magnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	// Check if the enemy approaches
	if(en_instance.pos.y < 0.1){
		set_animation_state(ATTACKING);
	}
    if (en_instance.pos.y < 0) {
        
		if(rand()%1000 == 0){
			set_animation_state(MOVING);
			bullet_manager->spawn_bullet(en_instance.pos, {0,-0.01}, HOSTILE, bullet_type);
			current_state = MOVE_ORIGIN; // Switch to IDLE_ORIGIN state
	        return; // Stop further movement processing		
		}
	}		
    if (magnitude > 0) {
        direction.x /= magnitude;
        direction.y /= magnitude;
    }

    // Move towards the origin at the given speed
    en_instance.pos.x += direction.x * speed;
    if(en_instance.pos.y > -0.35){
    en_instance.pos.y -= direction.y * speed;	
	}else{
		if(rand()%50 == 0){
			bullet_manager->spawn_bullet(en_instance.pos, {0,-0.01}, HOSTILE, bullet_type);
		}
	}
}

void Enemy::idle(){
	
	if(rand()%1000==0){bullet_manager->spawn_bullet(en_instance.pos, {0,-0.01}, HOSTILE, bullet_type);
	}
	if(rand()%10000 == 0){
		set_animation_state(MOVING);
		current_state = WANDER;
	
	}
	if(rand()%10000 == 0){
		set_animation_state(MOVING);
		current_state = MOVE_PLAYER;
	
	}
}
void Enemy::wander(){
	float distance = sqrt(pow(target.x - en_instance.pos.x, 2) + pow(target.y - en_instance.pos.y, 2));
    v2 direction = {target.x - en_instance.pos.x, target.y - en_instance.pos.y};
    
    if(distance <= 0.1){
    	set_animation_state(ATTACKING);
	}
    
	if(distance <= 0.02){
		set_animation_state(MOVING);
		// set new random target (CHANGE THIS MESS)
        target = {-0.9f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.9f + 0.9f))),
        -0.4f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.9f - -0.4f)))};
        
        distance = sqrt(pow(target.x - en_instance.pos.x, 2) + pow(target.y - en_instance.pos.y, 2));
        direction = {target.x - en_instance.pos.x, target.y - en_instance.pos.y};
        bullet_manager->spawn_bullet(en_instance.pos, {0,-0.01}, HOSTILE, bullet_type);
	}
    if (distance > 0) {
    direction.x /= distance;
    direction.y /= distance;
	}

    // Move towards the origin at the given speed
    en_instance.pos.x += direction.x * speed * (0.1+distance*0.7);
    en_instance.pos.y += direction.y * speed * (0.1+distance*0.7);
	
	if(rand()%5000){
		current_state = IDLE_ORIGIN;
	}
	if(rand()%5000){
		current_state = MOVE_ORIGIN;
	}
}

void Enemy::update_player_pos(v2 pos){
	player_pos = pos;
}

/*

			EnemyInfo en_info;
			en_info.ai_type=PASSIVE;
			en_info.idle_animation = WIGGLE; 
			en_info.attack_animation = ROTO_Y_FAST; 
			en_info.movement_animation = NONE;
			en_info.instance_model = TETRAHEDRA_STACKED; 
			en_info.bullet_type = SINGLE_SHOT;
			en_info.draw_type = DEFAULT_ENEMY_DRAW;
            
*/





EnemyInfo get_enemy_info_from_type(EnemyType enemy_type){
	EnemyInfo en_info;
	switch(enemy_type){
		case TETRA: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,TETRAHEDRON,DEFAULT_ENEMY_DRAW,PASSIVE,7,0.01,0.05);break;
		case BIG_TETRA: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,TETRAHEDRON,DEFAULT_ENEMY_DRAW,PASSIVE,35,0.005,0.12);break;
		case ELITE_TETRA: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,TETRAHEDRON,ELITE_ENEMY_DRAW,PASSIVE,20,0.015,0.05);break;
		case ICO: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,ICOSAHEDRON,DEFAULT_ENEMY_DRAW,PASSIVE,7,0.01,0.05);break;
		case BIG_ICO: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,ICOSAHEDRON,DEFAULT_ENEMY_DRAW,PASSIVE,35,0.015,0.12);break;
		case ELITE_ICO: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,ICOSAHEDRON,ELITE_ENEMY_DRAW,PASSIVE,20,0.015,0.05);break;
		case OCT: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,OCTAHEDRON,DEFAULT_ENEMY_DRAW,PASSIVE,7,0.01,0.05);break;
		case BIG_OCT: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,OCTAHEDRON,DEFAULT_ENEMY_DRAW,PASSIVE,35,0.015,0.12);break;
		case ELITE_OCT: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,OCTAHEDRON,ELITE_ENEMY_DRAW,PASSIVE,20,0.015,0.05);break;
		case DOUBLE_OCT: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,ENEMY_DOUBLE_OCT,DEFAULT_ENEMY_DRAW,PASSIVE,7,0.01,0.05);break;
		case BIG_DOUBLE_OCT: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,ENEMY_DOUBLE_OCT,DEFAULT_ENEMY_DRAW,PASSIVE,35,0.015,0.12);break;
		case ELITE_DOUBLE_OCT: 
			en_info = EnemyInfo(SINGLE_SHOT,ROTO_ALL,NONE,ROTO_Y_FAST,ENEMY_DOUBLE_OCT,ELITE_ENEMY_DRAW,PASSIVE,20,0.015,0.05);break;
	}
	return en_info;
}
