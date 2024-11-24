#pragma once
#include <GL/glew.h>

class Ball {
public:
	
	GLUquadricObj* qobj;
	float radius;
	float slices;
	float stacks;

	Ball(float radius_, float slices_, float stacks_);
		
};
