#pragma once
#include "object.h"

class Cylinder:public Object {
public:
	Cylinder(std::string name);

	void update(float delta_time) override;

};