#include "ring.h"

Ring::Ring(std::string name) :Object(name)
{
	color = glm::vec3(0, 1, 0);
	scale = glm::vec3(0.1, 0.05, 0.1);
}

void Ring::update(float delta_time)
{
	rotation.y += 3;
	Object::update(delta_time);

}

