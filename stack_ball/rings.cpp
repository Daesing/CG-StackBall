#include "rings.h"
#include <cstdlib>
#include <ctime>
#include "func.h"

Rings::Rings(int count) {
    for (int i = 0; i < count; ++i) {
        Ring ring("ring.obj");
        rings.push_back(ring);
    }
    stack_rings();
}

void Rings::update(float delta_time) {
    for (Ring& ring : rings) {
        ring.update(delta_time);
    }
}

void Rings::stack_rings() {
    float baseHeight = 0.0f;
    for (int i = 0; i < rings.size(); ++i) {
        rings[i].position.y = baseHeight - i;
        rings[i].rotation.y = baseHeight + i*3;
    }
}

void Rings::buffer()
{
    for (Ring& ring : rings) {
        InitBuffer(ring);
    }
}

void Rings::draw(GLint modelLocation)
{
    for (Ring& ring : rings) {
        ring.draw(modelLocation);
    }
}

