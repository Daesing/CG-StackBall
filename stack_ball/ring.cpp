#include "ring.h"
#include "func.h"

Ring::Ring() {
    for (int i = 1; i <= 6; ++i) {
        std::string fileName = "segment" + std::to_string(i) + ".obj";
        Segment segment(fileName);
        ring.push_back(segment);
    }
}

void Ring::update(float delta_time) {
    for (Segment& segment : ring) {
        segment.rotation.y += 80 * delta_time;
        segment.update(delta_time);
    }
}


void Ring::buffer()
{
    for (Segment& segment : ring) {
        InitBuffer(segment);
    }
}

void Ring::draw(GLint modelLocation)
{
    for (Segment& segment : ring) {
        segment.draw(modelLocation);
    }
}
