#include "enemy.h"
#include <cstdlib>

            
Enemy::Enemy() {}
Enemy::Enemy(BulletManager* bullet_manager, BGPlane* background,  v2 pos, InstanceType enemy_type) 
	: bullet_manager(bullet_manager), background(background), origin(pos) {
		
		target = origin;
		en_instance = Instance({0,1},0.05,get_model_from_type(static_cast<ModelType>(rand()%8)), DEFAULT_ENEMY_INSTANCE);
            
        Animation animation = get_animation_from_type(static_cast<AnimationType>(rand()%8));
        en_instance.add_animation(animation);

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
				
				// some logic like damage and piercing can be added here
				exists = false;
				bullet_manager->bullets[i].exists = false;
			}
		}
	}
}


void Enemy::update_state_machine(){
	switch(current_state){
	
	case IDLE_ORIGIN: idle(); break;
	case IDLE_SOMEWHERE: break;
	case DEFAULT_SHOOTING: break;
	case MOVE_ORIGIN: move_to_origin(); break;
	case MOVE_PLAYER: move_to_player(); break;
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
	// Check if the enemy is close enough to the origin
    if (en_instance.pos.y < 0) {
        
		if(rand()%1000 == 0){
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
		
		current_state = WANDER;
	
	}
	if(rand()%10000 == 0){
		
		current_state = MOVE_PLAYER;
	
	}
}
void Enemy::wander(){
	float distance = sqrt(pow(target.x - en_instance.pos.x, 2) + pow(target.y - en_instance.pos.y, 2));
    v2 direction = {target.x - en_instance.pos.x, target.y - en_instance.pos.y};
	if(distance <= 0.02){
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
