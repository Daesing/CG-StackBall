#include "segment.h"

Segment::Segment(std::string name):Object(name)
{
	color = glm::vec3(0, 1, 0);
	scale = glm::vec3(0.1, 0.1, 0.1);
	position = glm::vec3(-3, 0, 0);
}

void Segment::update(float delta_time)
{
	Object::update(delta_time);
}

