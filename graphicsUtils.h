#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

#include <vector>
#include <string>
#include "gameConstants.h"

struct v2 {
    float x;
    float y;
};

struct v3 {
    float x;
    float y;
    float z;
};

// Operator declarations
v2 operator+ (v2 p1, v2 p2);
v3 operator+ (v3 p1, v3 p2);
v3 v2_v3(v2 in);

// OpenGL utility functions declarations
void glVert3(v3 v);
void glVert(v2 v);
void glCol(v3 v);

class triangle {
public:
    triangle(v3 f, v3 s, v3 t);
    //void set_lines(bool v);
    //bool is_lines();
    void draw(v3 offset, bool lines);

    //bool lines;
    v3 vert1, vert2, vert3;
    v3 offset;
};

class object3d {
public:
    std::vector<triangle> triangles;
    v3 translation;

    void move(v3 offset);
    void draw(bool lines);
    void normalize();
    void scale(v3 scaling_factor, bool scale_mode);
    void rotate(v3 rvec, v3 center);
};

object3d load_obj(const std::string& filename);
object3d get_model_from_type(int type);

#endif // GRAPHICS_UTILS_H
