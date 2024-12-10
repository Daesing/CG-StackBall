#pragma once
#include "object.h"

class Segment:public Object {
public:
	Segment(std::string);

	void update(float delta_time) override;
};