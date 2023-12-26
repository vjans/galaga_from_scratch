#ifndef INSTANCE_H
#define INSTANCE_H
#include "graphicsUtils.h"
#include "gameConstants.h"

class Instance{
	public:
	v2 pos;
	// assuming all quadratic hitboxes
	float size;
	bool draw_bounding_box = false;
	object3d model;
	InstanceType instance_type;	
	
	Instance(){}
	Instance(v2 _pos, float _size, object3d _model, InstanceType _instance_type)
		: pos(_pos), size(_size), model(_model), instance_type(_instance_type){
			
		model.normalize();
		v3 scalef; scalef.x = size; scalef.y = size; scalef.z = size;
		model.scale(scalef, true);
	}
	void draw();
	void animate(float time);
	bool check_collision(const Instance& other) const;
};

#endif
