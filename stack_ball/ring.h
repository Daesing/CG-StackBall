#pragma once
#include "segment.h"
#include <deque>

class Ring {
public:
	std::deque<Segment> ring;
	std::vector<int>remove_index;
	bool broken{ false };
	bool destroyed{ false };
	glm::vec3 position = glm::vec3(0.0f);
	float rotation{ 80 };
	Ring();

	void break_ring(float delta_time,glm::vec3,int&);
	void update(float delta_time);
	void buffer();
	void draw(GLint);
};


