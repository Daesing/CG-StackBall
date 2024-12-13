#pragma once

#include <vector>
#include "ring.h"

class Rings {
public:
    std::vector<Ring> rings;

    Rings(int count);
    void update(float delta_time);
    void stack_rings();
    void draw(GLint);
    void buffer();
};

