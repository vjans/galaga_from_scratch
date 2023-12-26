#include "GraphicsUtils.h"
#include "gameConstants.h"
#include <GL/gl.h> 
#include <GL/glu.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath> // For sin() and cos()

/*
@@@@@@@@@@@@@@@@
HELPER FUNCTIONS
@@@@@@@@@@@@@@@@
*/
// Function to rotate a point around an axis by a given angle
v3 rotate_point_around_axis(v3 point, v3 axis, float angle) {
    // Normalize the axis vector
    float axisLength = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    v3 nAxis = {axis.x / axisLength, axis.y / axisLength, axis.z / axisLength};

    // Using Rodrigues' rotation formula
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    return {
        point.x * cosAngle + sinAngle * (nAxis.y * point.z - nAxis.z * point.y) + (1 - cosAngle) * nAxis.x * (nAxis.x * point.x + nAxis.y * point.y + nAxis.z * point.z),
        point.y * cosAngle + sinAngle * (nAxis.z * point.x - nAxis.x * point.z) + (1 - cosAngle) * nAxis.y * (nAxis.x * point.x + nAxis.y * point.y + nAxis.z * point.z),
        point.z * cosAngle + sinAngle * (nAxis.x * point.y - nAxis.y * point.x) + (1 - cosAngle) * nAxis.z * (nAxis.x * point.x + nAxis.y * point.y + nAxis.z * point.z)
    };
}

/*
@@@@@@@@@@@@@@
VECS+TRIANGLES
@@@@@@@@@@@@@@
*/

// Operator implementations for v2 and v3
v2 operator+ (v2 p1, v2 p2) {
    v2 out;
    out.x = p1.x + p2.x;
    out.y = p1.y + p2.y;
    return out;
}

v3 operator+ (v3 p1, v3 p2) {
    v3 out;
    out.x = p1.x + p2.x;
    out.y = p1.y + p2.y;
    out.z = p1.z + p2.z;
    return out;
}

// Subtraction
v2 operator- (const v2& p1, const v2& p2) {
    return {p1.x - p2.x, p1.y - p2.y};
}

// Scalar multiplication
v2 operator* (const v2& p, float scalar) {
    return {p.x * scalar, p.y * scalar};
}

// Scalar division
v2 operator/ (const v2& p, float scalar) {
    // Check for division by zero
    if (scalar == 0) return {0,0};
    return {p.x / scalar, p.y / scalar};
}

// Equality comparison
bool operator== (const v2& p1, const v2& p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
}

v3 v2_v3(v2 in) {
    v3 out;
    out.x = in.x;
    out.y = in.y;
    out.z = 0;
    return out;
}

// Subtraction
v3 operator- (const v3& p1, const v3& p2) {
    return {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}

// Scalar multiplication
v3 operator* (const v3& p, float scalar) {
    return {p.x * scalar, p.y * scalar, p.z * scalar};
}

// Scalar division
v3 operator/ (const v3& p, float scalar) {
    // Check for division by zero
    if (scalar == 0) return {0,0};
    return {p.x / scalar, p.y / scalar, p.z / scalar};
}

// Equality comparison
bool operator== (const v3& p1, const v3& p2) {
    return (p1.x == p2.x) && (p1.y == p2.y) && (p1.z == p2.z);
}



// OpenGL utility functions implementations

void glVert3(v3 v) {
    glVertex3f(v.x, v.y, v.z);
}

void glVert(v2 v) {
    glVertex3f(v.x, v.y, 0);
}

void glCol(v3 v) {
    glColor3f(v.x, v.y, v.z);
}


// triangle methods implementation

triangle::triangle(v3 f, v3 s, v3 t) {
    vert1 = f;
    vert2 = s;
    vert3 = t;
    offset.x = 0;
    offset.y = 0;
    offset.z = 0;
}


void triangle::draw(v3 offset, bool lines) {
    if (lines) {
        glBegin(GL_LINES);
        glVert3(vert1 + offset);
        glVert3(vert2 + offset);
        glVert3(vert2 + offset);
        glVert3(vert3 + offset);
        glVert3(vert3 + offset);
        glVert3(vert1 + offset);
        glEnd();
    } else {
        glBegin(GL_TRIANGLES);
        glVert3(vert1 + offset);
        glVert3(vert2 + offset);
        glVert3(vert3 + offset);
        glEnd();
    }
}

/*
@@@@@@@@
OBJECT3D
@@@@@@@@
*/

// object3d methods implementation
void object3d::move(v3 offset) {
    translation.x = offset.x;
    translation.y = offset.y;
    translation.z = offset.z;
}

void object3d::draw(bool lines) {
    std::vector<triangle>::iterator it;

    for (it = triangles.begin(); it != triangles.end(); ++it) {
            it->draw(translation, lines);
    }
}

void object3d::normalize(){
	if (triangles.empty()) return;

    v3 minPoint = triangles[0].vert1;
    v3 maxPoint = triangles[0].vert1;

	// Find min and max points
    for (size_t i = 0; i < triangles.size(); i++) {
        const triangle& t = triangles[i];

        // Update min and max for each vertex of the triangle
        minPoint.x = std::min(minPoint.x, std::min(t.vert1.x, std::min(t.vert2.x, t.vert3.x)));
        minPoint.y = std::min(minPoint.y, std::min(t.vert1.y, std::min(t.vert2.y, t.vert3.y)));
        minPoint.z = std::min(minPoint.z, std::min(t.vert1.z, std::min(t.vert2.z, t.vert3.z)));

        maxPoint.x = std::max(maxPoint.x, std::max(t.vert1.x, std::max(t.vert2.x, t.vert3.x)));
        maxPoint.y = std::max(maxPoint.y, std::max(t.vert1.y, std::max(t.vert2.y, t.vert3.y)));
        maxPoint.z = std::max(maxPoint.z, std::max(t.vert1.z, std::max(t.vert2.z, t.vert3.z)));
    }

    // Calculate scale factors for each axis
    v3 scalev;
    scalev.x = (maxPoint.x - minPoint.x) / 2.0f;
    scalev.y = (maxPoint.y - minPoint.y) / 2.0f;
    scalev.z = (maxPoint.z - minPoint.z) / 2.0f;

    // Avoid division by zero
    if (scalev.x == 0) scalev.x = 1;
    if (scalev.y == 0) scalev.y = 1;
    if (scalev.z == 0) scalev.z = 1;

    // Calculate center of the bounding box
    v3 center;
    center.x = -(maxPoint.x + minPoint.x) / 2.0f;
    center.y = -(maxPoint.y + minPoint.y) / 2.0f;
    center.z = -(maxPoint.z + minPoint.z) / 2.0f;

    // Translate the model to the origin
    v3 translation = center;
    for (size_t i = 0; i < triangles.size(); i++) {
        triangle& t = triangles[i];

        t.vert1 = t.vert1+translation;
        t.vert2 = t.vert2+translation;
        t.vert3 = t.vert3+translation;
    }

    // Scale the model
    scalev.x = 1/scalev.x;
    scalev.y = 1/scalev.y;
    scalev.z = 1/scalev.z;
    
    scale(scalev, false);

}

void object3d::scale(v3 scaling_factor, bool scale_mode){
	if(scale_mode == 1){
	
		for (size_t i = 0; i < triangles.size(); i++) {
		    triangle& t = triangles[i];
		
		    t.vert1.x *= scaling_factor.x;
		    t.vert1.y *= scaling_factor.y;
		    t.vert1.z *= scaling_factor.z;
		
		    t.vert2.x *= scaling_factor.x;
		    t.vert2.y *= scaling_factor.y;
		    t.vert2.z *= scaling_factor.z;
		
		    t.vert3.x *= scaling_factor.x;
		    t.vert3.y *= scaling_factor.y;
		    t.vert3.z *= scaling_factor.z;
		}	
	}
	
	if(scale_mode == 0){
		float max_fac = 2e32;
		
		if(scaling_factor.x < max_fac){
			max_fac = scaling_factor.x;
		}
		if(scaling_factor.y < max_fac){
			max_fac = scaling_factor.y;
		}
		if(scaling_factor.z < max_fac){
			max_fac = scaling_factor.z;
		}
		for (size_t i = 0; i < triangles.size(); i++) {
		    triangle& t = triangles[i];
		
		    t.vert1.x *= max_fac;
		    t.vert1.y *= max_fac;
		    t.vert1.z *= max_fac;
		
		    t.vert2.x *= max_fac;
		    t.vert2.y *= max_fac;
		    t.vert2.z *= max_fac;
		
		    t.vert3.x *= max_fac;
		    t.vert3.y *= max_fac;
		    t.vert3.z *= max_fac;
		}	
	}
}



void object3d::rotate(v3 rvec, v3 center) {
    // Rotate around the X axis
    for (size_t i = 0; i < triangles.size(); i++) {
        triangle& t = triangles[i];
        
        t.vert1 = rotate_point_around_axis(t.vert1 - center, {1, 0, 0}, rvec.x) + center;
        t.vert2 = rotate_point_around_axis(t.vert2 - center, {1, 0, 0}, rvec.x) + center;
        t.vert3 = rotate_point_around_axis(t.vert3 - center, {1, 0, 0}, rvec.x) + center;

        // Rotate around the Y axis
        t.vert1 = rotate_point_around_axis(t.vert1 - center, {0, 1, 0}, rvec.y) + center;
        t.vert2 = rotate_point_around_axis(t.vert2 - center, {0, 1, 0}, rvec.y) + center;
        t.vert3 = rotate_point_around_axis(t.vert3 - center, {0, 1, 0}, rvec.y) + center;

        // Rotate around the Z axis
        t.vert1 = rotate_point_around_axis(t.vert1 - center, {0, 0, 1}, rvec.z) + center;
        t.vert2 = rotate_point_around_axis(t.vert2 - center, {0, 0, 1}, rvec.z) + center;
        t.vert3 = rotate_point_around_axis(t.vert3 - center, {0, 0, 1}, rvec.z) + center;
    }
}

object3d load_obj(const std::string& filename) {
    std::ifstream file(filename.c_str());
    object3d model;

    char line[256]; // Character array to store each line of the file

    std::vector<v3> vertices;
    size_t current_triangle = 0;

    while (file.getline(line, 256)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;


        if (prefix == "v") {
            v3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        }
        else if (prefix == "f") {
            int index;
            int indices[3];
            for (int i = 0; i < 3; ++i) {
                iss >> index;
                indices[i] = index;
            }
            v3 def; def.x = 1; def.y = 1; def.z = 1;

            triangle t(vertices[indices[0] - 1], vertices[indices[1] - 1], vertices[indices[2] - 1]);
            model.triangles.push_back(t);
            ++current_triangle;
        }
    }
    return model;
}

object3d get_model_from_type(int type){
	v3 col;
	col.x = 1;
	col.y = 1;
	col.z = 1;

	std::vector<v3> colors;
	std::vector<bool> line_types;

	colors.push_back(col);
	line_types.push_back(true);
	switch(type){
		case 0:
			return load_obj("assets/objects/enemy_double_oct.obj");
		case 1:
			return load_obj("assets/objects/item.obj");
		case 2:
			return load_obj("assets/objects/icosahedron.obj");
		case 3:
			return load_obj("assets/objects/triangle.obj");
		case 4:
			return load_obj("assets/objects/player_model.obj");
		case 5:
			return load_obj("assets/objects/enemy_double_oct.obj");
	}
}



