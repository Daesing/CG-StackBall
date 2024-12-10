#include "cylinder.h"

Cylinder::Cylinder(std::string name) :Object(name) {
	scale = glm::vec3(0.1, 0.5, 0.1);
	color = glm::vec3(0.0f, 0.0f, 1.0f);
	position = glm::vec3(0.0f, -5.0f, -2.0f);
}

void Cylinder::update(float delta_time)
{
	Object::update(delta_time);
}

