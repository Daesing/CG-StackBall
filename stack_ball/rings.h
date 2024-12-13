#pragma once

#include <vector>
#include "ring.h"

class Rings {
public:
    std::vector<Ring> rings;
    int count{};

    Rings(int count);
    void update(float delta_time);
    void stack_rings();
    void buffer();
    void draw(GLint);
};

