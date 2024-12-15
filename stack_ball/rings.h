#pragma once

#include <deque>
#include "ring.h"

class Rings {
public:
    std::deque<Ring> rings;

    Rings(int count);
    void update(float delta_time, bool mouse_state, glm::vec3 ball_pos);
    void stack_rings();
    void draw(GLint);
    void buffer();
    void add_ring();
    void reset_game();
};

