#pragma once

#include <deque>
#include "ring.h"

class Rings {
public:
    std::deque<Ring> rings;
    int level{ 0 };

    Rings(int count);
    void update(float delta_time, bool mouse_state, glm::vec3 ball_pos,int& crushed_stack);
    void stack_rings();
    void draw(GLint);
    void buffer();
    void add_ring();
    void set_pos();
    void set_level(int& score);
    void increase_rotation();
};

