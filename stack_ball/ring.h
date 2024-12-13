#pragma once
#include "object.h"

class Ring :public Object {
public:
	Ring(std::string);

	void update(float delta_time) override;


};