#include "cylinder.h"


Cylinder cylinder(1.0, 1.0, 2.0, 20, 8);

Cylinder::Cylinder(float base_r, float top_r, float height_, float slices_, float stacks_) {
	base_radius = base_r;
	top_radius = top_r;
	height = height_;
	slices = slices_;
	stacks = stacks_;

	qobj = gluNewQuadric();
}


