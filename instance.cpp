#include "Instance.h"
#include "graphicsUtils.h"

// Implement the draw function
void Instance::draw() {
    // Assuming 'model' has a method to handle its own rendering
	switch(instance_type){
		case DEFAULT_BULLET_INSTANCE:
		    model.move(v2_v3(pos));
		    glCol({1,1,1});
		    model.draw(DRAW_MODE_FILL);
			break;
		case DEFAULT_PLAYER_INSTANCE:
		    model.move(v2_v3(pos));
		    glCol({1,1,1});
		    model.draw(DRAW_MODE_FILL);
		    model.scale({1.1,1.1,1.1}, SCALE_MODE_FACTOR);
		    glCol({0,0,0});
		    model.draw(DRAW_MODE_LINE);
		    model.scale({1/1.1,1/1.1,1/1.1}, SCALE_MODE_FACTOR);
			break;
		case DEFAULT_ENEMY_INSTANCE:
		    model.move(v2_v3(pos));
		    glCol({1,1,1});
		    model.draw(DRAW_MODE_FILL);
		    model.scale({1.1,1.1,1.1}, SCALE_MODE_FACTOR);
		    glCol({0,0,0});
		    model.draw(DRAW_MODE_LINE);
		    model.scale({1/1.1,1/1.1,1/1.1}, SCALE_MODE_FACTOR);
			break;
		default:
		    model.move(v2_v3(pos));
		    glCol({1,1,1});
		    model.draw(DRAW_MODE_LINE);
	}

	if(draw_bounding_box){
		glBegin(GL_LINES);
		glCol({0,1,0});
		glVertex3f(pos.x-size,pos.y-size,0);
		glVertex3f(pos.x+size,pos.y-size,0);
		glVertex3f(pos.x+size,pos.y-size,0);
		glVertex3f(pos.x+size,pos.y+size,0);
		glVertex3f(pos.x+size,pos.y+size,0);
		glVertex3f(pos.x-size,pos.y+size,0);
		glVertex3f(pos.x-size,pos.y+size,0);
		glVertex3f(pos.x-size,pos.y-size,0);
		glEnd();
	}
}

void Instance::animate(float time){
	
	if(animations.size() == 0 || current_animation_index == NO_ANIMATION)return;
	
	model.rotate(animations[current_animation_index].get_rv(time),animations[current_animation_index].get_cv(time));
	
}

void Instance::add_animation(Animation animation){
	animations.push_back(animation);
	current_animation_index++;
}
/*enum AnimationType{
	NONE,
	WIGGLE,
	WIGGLE_FAST,
	ROTO_X,
	ROTO_Y,
	ROTO_Z,
	ROTO_X_FAST,
	ROTO_Y_FAST,
	ROTO_Z_FAST,
};

*/
Animation get_animation_from_type(AnimationType animation_type){

	
	v3 base_rotation = {0,0,0};
	v3 base_center = {0,0,0};
	
	// roto_trig_params: params.x = phase, params.y = shift, params.z = amplitude
	v3 x_roto_trig_params = {0,0,0};
	v3 y_roto_trig_params = {0,0,0};
	v3 z_roto_trig_params = {0,0,0};
	
	v3 x_center_trig_params = {0,0,0};
	v3 y_center_trig_params = {0,0,0};
	v3 z_center_trig_params = {0,0,0};
	
	
	switch(animation_type){
		case NONE: break;
		case WIGGLE: base_rotation = {0,0.02,0}; z_roto_trig_params = {0.1,3.141592/2,1/33.0f};break;
		case WIGGLE_FAST: base_rotation = {0,0.02,0}; z_roto_trig_params = {0.2,3.141592/2,1/33.0f}; break;
		case ROTO_X: base_rotation = {0.02,0,0}; break;
		case ROTO_Y: base_rotation = {0,0.02,0}; break;
		case ROTO_Z: base_rotation = {0,0,0.02}; break;
		case ROTO_X_FAST: base_rotation = {0.1,0,0}; break;
		case ROTO_Y_FAST: base_rotation = {0,0.1,0}; break;
		case ROTO_Z_FAST: base_rotation = {0,0,0.1}; break;
	}
	
	return Animation(base_rotation,base_center,x_roto_trig_params,y_roto_trig_params,
	z_roto_trig_params,x_center_trig_params,y_center_trig_params,z_center_trig_params);
}

bool Instance::check_collision(const Instance& other) const {
        float left1 = pos.x - size;
        float right1 = pos.x + size;
        float top1 = pos.y + size;
        float bottom1 = pos.y - size;

        float left2 = other.pos.x - other.size;
        float right2 = other.pos.x + other.size;
        float top2 = other.pos.y + other.size;
        float bottom2 = other.pos.y - other.size;

        bool xOverlap = (left1 < right2) && (right1 > left2);
        bool yOverlap = (bottom1 < top2) && (top1 > bottom2);

        return xOverlap && yOverlap;
    }
