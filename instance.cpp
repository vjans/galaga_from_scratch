#include "Instance.h"
#include "graphicsUtils.h"
// Include necessary OpenGL headers
#include <GL/gl.h>
#include <math.h>

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
	v3 neutral = {0,0,0};
	switch(instance_type){
		case DEFAULT_BULLET_INSTANCE:
				//model.rotate({0.00,0.05,0.00},neutral);
			break;
		case DEFAULT_PLAYER_INSTANCE:
			break;
		case DEFAULT_ENEMY_INSTANCE:
				model.rotate({0.00,0.02,((float)sin(time*0.1+3.141592/2))/33.0f},neutral);
			break;
		default:
				model.rotate({0.03,0.03,0.03},neutral);
			break;
	}
	
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
