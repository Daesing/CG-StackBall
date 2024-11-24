#include "ball.h"


Ball ball(0.5, 50, 50);

Ball::Ball(float radius_, float slices_, float stacks_) {

	radius = radius_;
	slices = slices_;
	stacks = stacks_;
	
	qobj = gluNewQuadric();

}