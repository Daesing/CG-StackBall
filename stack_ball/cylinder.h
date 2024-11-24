#pragma once
#include <GL/glew.h>

class Cylinder {
public:

	GLUquadricObj* qobj;
	float base_radius;
	float top_radius;
	float height;
	float slices;
	float stacks;

	Cylinder(float,float,float,float,float);

};
