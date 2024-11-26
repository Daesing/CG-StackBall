#pragma once
#include <GL/glew.h>
#include <gl/glm/gtc/matrix_transform.hpp>

class Cylinder {
public:

	GLUquadricObj* qobj;
	float base_radius;
	float top_radius;
	float height;
	float slices;
	float stacks;

	glm::mat4 model_matrix = glm::mat4(1.0f);

	Cylinder(float,float,float,float,float);

};
