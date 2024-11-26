#pragma once
#include <GL/glew.h>
#include <gl/glm/gtc/matrix_transform.hpp>

class Ball {
public:
	
	GLUquadricObj* qobj;
	float radius;
	float slices;
	float stacks;

	glm::mat4 model_matrix = glm::mat4(1.0f);

	Ball(float radius_, float slices_, float stacks_);
		
};
