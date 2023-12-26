#include "Player.h"

Player::Player(){
}
Player::Player(BulletManager* bullet_manager, BGPlane* background, Instance player_instance)
    : bullet_manager(bullet_manager), background(background), pl_instance(player_instance), 
      speed(0.01), shoot_delay(5), shoot_delay_counter(0) {
    
    std::fill(std::begin(keys_pressed), std::end(keys_pressed), false);
}

void Player::move() {
    if (keys_pressed[0] && pl_instance.pos.x > -1 + pl_instance.size) {
        pl_instance.pos.x -= speed;
        moving_left = true;
    }else{
    	moving_left = false;
	}
    if (keys_pressed[1] && pl_instance.pos.x < 1 - pl_instance.size) {
        pl_instance.pos.x += speed;
    	moving_right = true;
	}else{
		moving_right = false;
	}
}

void Player::draw() {
	pl_instance.draw();
}
void Player::animate(float time){
	pl_instance.animate(time);
	
	
	//rotate model left or right when movement starts
	if(moving_left){
		if(total_rotation < 0.4){
			pl_instance.model.rotate({0,0.04,0},{0,0,0});
			total_rotation+=0.04;	
		}
	}else if(moving_right){
		if(total_rotation > -0.4){
		pl_instance.model.rotate({0,-0.04,0},{0,0,0});
		total_rotation+=-0.04;	
		}
	}else{
		//slowly reset rotation
		if(total_rotation != 0 && total_rotation < 0.001 && total_rotation > -0.001){
			total_rotation = 0;
		}else if(total_rotation > 0){
			total_rotation-=0.04;
			pl_instance.model.rotate({0,-0.04,0},{0,0,0});
		}else if(total_rotation < 0){
			total_rotation+=0.04;
			pl_instance.model.rotate({0,0.04,0},{0,0,0});
		}
	}

}

void Player::shoot() {
    if (keys_pressed[4]) {
        shoot_delay_counter--;
        if (shoot_delay_counter <= 0) {
            shoot_delay_counter = shoot_delay;
            v2 forward = {0.0, 0.01};
            bullet_manager->spawn_bullet(pl_instance.pos, forward, FRIENDLY, DOUBLE_SHOT);
        }
    }
}

void Player::check_collision(){
	for(int i = 0; i < BULLET_BUFFER_MAX; i++){
		if(bullet_manager->bullets[i].exists && bullet_manager->bullets[i].alignment == HOSTILE){
			bool collides = pl_instance.check_collision(bullet_manager->bullets[i].instance);
			if(collides){
				
				// some logic like damage and piercing can be added here
				bullet_manager->bullets[i].exists = false;
			}
		}
	}
}
