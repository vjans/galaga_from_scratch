#include "enemy.h"
#include <cstdlib>

Enemy::Enemy() {}
Enemy::Enemy(BulletManager* bullet_manager, BGPlane* background,  Instance enemy_instance) 
	: bullet_manager(bullet_manager), background(background), en_instance(enemy_instance) {

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
        bullet_manager->spawn_bullet(en_instance.pos, forward, HOSTILE, SINGLE_SHOT);
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