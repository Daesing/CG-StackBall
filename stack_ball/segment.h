#pragma once
#include "object.h"

class Segment : public Object {
public:
    Segment(std::string name);

    void update(float delta_time) override;
    void draw(GLint modelLocation) override;
};
