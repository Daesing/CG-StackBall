#include "rings.h"
#include <cstdlib>
#include <ctime>
#include "func.h"

Rings::Rings(int count) {
    for (int i = 0; i < count; ++i) {
        Ring ring;
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
        for (int j = 0; j < rings[i].ring.size(); ++j) {
            rings[i].ring[j].position.y = baseHeight - i;
            rings[i].ring[j].rotation.y = baseHeight + i * 3;
        }
    }
}

void Rings::draw(GLint modelLocation)
{
    for (Ring& ring : rings) {
        ring.draw(modelLocation);
    }
}

void Rings::buffer()
{
    for (Ring& ring : rings) {
        ring.buffer();
    }
}

