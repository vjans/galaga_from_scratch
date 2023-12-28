#ifndef INSTANCE_H
#define INSTANCE_H
#include "graphicsUtils.h"
#include "gameConstants.h"
#include <GL/gl.h>
#include <math.h>

class Animation{
public:
	v3 base_rotation = {0,0,0};
	v3 base_center = {0,0,0};
	
	// roto_trig_params: params.x = phase, params.y = shift, params.z = amplitude
	v3 x_roto_trig_params = {0,0,0};
	v3 y_roto_trig_params = {0,0,0};
	v3 z_roto_trig_params = {0,0,0};
	
	v3 x_center_trig_params = {0,0,0};
	v3 y_center_trig_params = {0,0,0};
	v3 z_center_trig_params = {0,0,0};
	
	// Constructor
    Animation(const v3& br, const v3& bc,
              const v3& x_rtp, const v3& y_rtp, const v3& z_rtp,
              const v3& x_ctp, const v3& y_ctp, const v3& z_ctp)
        : base_rotation(br), base_center(bc),
          x_roto_trig_params(x_rtp), y_roto_trig_params(y_rtp), z_roto_trig_params(z_rtp),
          x_center_trig_params(x_ctp), y_center_trig_params(y_ctp), z_center_trig_params(z_ctp) {}
          
          
	//	model.rotate({0.00,0.02,((float)sin(time*0.1+3.141592/2))/33.0f},neutral);
	v3 get_rv(float time){
		v3 out;
		out.x = base_rotation.x + ((float)sin(time*x_roto_trig_params.x+x_roto_trig_params.y)*x_roto_trig_params.z);
		out.y = base_rotation.y + ((float)sin(time*y_roto_trig_params.x+y_roto_trig_params.y)*y_roto_trig_params.z);
		out.z = base_rotation.z + ((float)sin(time*z_roto_trig_params.x+z_roto_trig_params.y)*z_roto_trig_params.z);
		return out;
	}
	v3 get_cv(float time){
		v3 out;
		out.x = base_center.x + ((float)sin(time*x_center_trig_params.x+x_center_trig_params.y)*x_center_trig_params.z);
		out.y = base_center.y + ((float)sin(time*y_center_trig_params.x+y_center_trig_params.y)*y_center_trig_params.z);
		out.z = base_center.z + ((float)sin(time*z_center_trig_params.x+z_center_trig_params.y)*z_center_trig_params.z);
		return out;
	}
};
Animation get_animation_from_type(AnimationType);

class Instance{
	public:
	v2 pos;
	// assuming all quadratic hitboxes
	float size;
	bool draw_bounding_box = false;
	object3d model;
	DrawType draw_type;	
	std::vector<Animation> animations;
	int current_animation_index = NO_ANIMATION;
	
	Instance(){}
	Instance(v2 _pos, float _size, object3d _model, DrawType _draw_type)
		: pos(_pos), size(_size), model(_model), draw_type(_draw_type){
			
		model.normalize();
		v3 scalef; scalef.x = size; scalef.y = size; scalef.z = size;
		model.scale(scalef, true);
	}
	void draw();
	void animate(float time);
	bool check_collision(const Instance& other) const;
	void add_animation(Animation animation);
};

#endif
