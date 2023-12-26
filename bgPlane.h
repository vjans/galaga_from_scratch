#ifndef BGPLANE_H
#define BGPLANE_H
#include <vector>
#include "graphicsUtils.h"
#include "gameConstants.h"

struct light{
	v2 pos;
	v3 color;
	float size;
};

class BGPlane{
public:
	const static int resolution = SCREEN_SIZE/2;
	v3 colors[resolution][resolution];
	v3 colors_with_light[resolution][resolution];
	
	std::vector<light> lights;
	void init();
	void draw(float time);
	void update(float time);
	void add_lights();
	void add_light(v2 pos, v3 col, float intensity);
};

#endif
