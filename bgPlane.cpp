#include "bgPlane.h"
#include "graphicsUtils.h"
// Include necessary OpenGL headers
#include <GL/gl.h>
#include <math.h>
#include <algorithm>

void BGPlane::draw(float time){
	
	for (int x = 0; x < resolution; x++) {
        for (int y = 0; y < resolution; y++) {
            colors_with_light[x][y] = colors[x][y];
        }
    }

	add_lights();
	float xc,yc,xcp,ycp;
	glBegin(GL_QUADS);
	for(int x = 0; x < resolution; x++){
		for(int y = 0; y < resolution; y++){
			glCol(colors_with_light[x][y]);
			
			
			
			xc = ((float)x*2 / ((float)resolution)-1);
			yc = ((float)y*2 / ((float)resolution)-1);
			xcp = ((float)(x+1)*2 / ((float)resolution)-1);
			ycp = ((float)(y+1)*2 / ((float)resolution)-1);
			glVertex3f(xc,yc,0.5);
			glVertex3f(xcp,yc,0.5);
			glVertex3f(xcp,ycp,0.5);
			glVertex3f(xc,ycp,0.5);
		}
	}
	glEnd();
	
	//clear lights for next frame
	lights.clear();
}

void BGPlane::add_lights() {
	
    
    for(int i = 0; i < lights.size(); i++) {
	    // Normalize and scale coordinates to grid indices
	    int min_x_index = static_cast<int>(((lights[i].pos.x - lights[i].size + 1) / 2.0) * resolution);
	    int max_x_index = static_cast<int>(((lights[i].pos.x + lights[i].size + 1) / 2.0) * resolution);
	    int min_y_index = static_cast<int>(((lights[i].pos.y - lights[i].size + 1) / 2.0) * resolution);
	    int max_y_index = static_cast<int>(((lights[i].pos.y + lights[i].size + 1) / 2.0) * resolution);
	
	    // Clamp indices to the bounds of the grid
	    min_x_index = std::max(0, std::min(min_x_index, resolution - 1));
	    max_x_index = std::max(0, std::min(max_x_index, resolution - 1));
	    min_y_index = std::max(0, std::min(min_y_index, resolution - 1));
	    max_y_index = std::max(0, std::min(max_y_index, resolution - 1));

        // Now you can use min_x_index, max_x_index, min_y_index, and max_y_index
        // to apply light effects on the grid within this range
        
        // Iterate over the affected grid area
        for (int x = min_x_index; x <= max_x_index; x++) {
            for (int y = min_y_index; y <= max_y_index; y++) {
                // Calculate normalized grid coordinates
                float gridX = (float)x / resolution * 2.0f - 1.0f;
                float gridY = (float)y / resolution * 2.0f - 1.0f;

                // Calculate distance from light to grid point
                float distance = sqrt(pow(gridX - lights[i].pos.x, 2) + pow(gridY - lights[i].pos.y, 2));

                // Adjust intensity based on distance
                float intensity = std::max(0.0f, 1.0f - distance / lights[i].size);

                // Update grid colors
                // Assuming colors is a member variable of BGPlane
                colors_with_light[x][y].x = std::min(1.0f, colors_with_light[x][y].x + intensity * lights[i].color.x);
                colors_with_light[x][y].y = std::min(1.0f, colors_with_light[x][y].y + intensity * lights[i].color.y);
                colors_with_light[x][y].z = std::min(1.0f, colors_with_light[x][y].z + intensity * lights[i].color.z);
            }
        }
    }
}

void BGPlane::add_light(v2 pos, v3 col, float intensity){
	light l;
	l.pos = pos;
	l.color = col;
	l.size = intensity;
	lights.push_back(l);
}

void BGPlane::update(float time){
	
}

void BGPlane::init(){
	for(int x = 0; x < resolution; x++){
		for(int y = 0; y < resolution; y++){
			colors[x][y] = {((float)x / ((float)resolution))*0.3, ((float)y / ((float)resolution))*0.3, 0.3};
		}
	}
}
