#pragma once
#include "segment.h"

class Ring {
public:
	std::vector<Segment> ring;

	Ring();
	void update(float delta_time);
	void buffer();
	void draw(GLint);
};


