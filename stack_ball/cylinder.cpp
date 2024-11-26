#include "cylinder.h"


Cylinder cylinder(0.5, 0.5, 5.0, 20, 8);

Cylinder::Cylinder(float base_r, float top_r, float height_, float slices_, float stacks_) {
	base_radius = base_r;
	top_radius = top_r;
	height = height_;
	slices = slices_;
	stacks = stacks_;

	qobj = gluNewQuadric();

	model_matrix = 
		glm::translate(model_matrix, glm::vec3(0.0, 2.0, 0.0)) *
		glm::rotate(model_matrix, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
}


