#include "BulletManager.h"

BulletManager::BulletManager() {
    // Initialize bullets array or other initializations
    for (int i = 0; i < BULLET_BUFFER_MAX; ++i) {
        bullets[i].exists = false;
    }
}

Bullet init_bullet_from_type(v2 pos, BulletType bullet_type){
	
	Bullet bullet;
	Instance bullet_instance;
	
	switch(bullet_type){
		case SINGLE_SHOT:
			bullet_instance = Instance(pos, 0.02, get_model_from_type(TRIANGLE), DEFAULT_BULLET_DRAW);
			break;
		case DOUBLE_SHOT:
			bullet_instance = Instance(pos, 0.02, get_model_from_type(TRIANGLE), DEFAULT_BULLET_DRAW);
			break;
	}
	
	bullet.instance = bullet_instance;
	return bullet;
}

void BulletManager::spawn_bullet(v2 pos, v2 dir, bool alignment, BulletType bullet_type) {
    for (int i = 0; i < BULLET_BUFFER_MAX; i++) {
        if (!bullets[i].exists) {
            
            bullets[i] = init_bullet_from_type(pos, bullet_type);
            bullets[i].exists = true;
            bullets[i].alignment = alignment;
            bullets[i].speed = dir; // add to bullet from type?? 
            
            break;
        }
    }
}

void BulletManager::draw_bullets(){
	for (int i = 0; i < BULLET_BUFFER_MAX; i++) {
        if (bullets[i].exists) {
            bullets[i].instance.draw();
        }
    }
}

void BulletManager::animate_bullets(float time){
	for (int i = 0; i < BULLET_BUFFER_MAX; i++) {
        if (bullets[i].exists) {
            bullets[i].instance.animate(time);
        }
    }
}
void BulletManager::move_bullets(){
	for(int i = 0; i < BULLET_BUFFER_MAX; i++) {
        if(bullets[i].exists) {
            bullets[i].instance.pos.x += bullets[i].speed.x;
            bullets[i].instance.pos.y += bullets[i].speed.y;
            
            if(bullets[i].instance.pos.y > 1.5 || bullets[i].instance.pos.y < -1.5 || bullets[i].instance.pos.x > 1.5 || bullets[i].instance.pos.x < -1.5){
            	bullets[i].exists = false;
			}
        }
    }
}


