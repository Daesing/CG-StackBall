#pragma once

#include "object.h"
#include "segment.h"
#include <vector>

class Platform : public Object {
public:
    std::vector<Segment> segments; // 플랫폼을 구성하는 세그먼트들
    float innerRadius;             // 중심 구멍 반지름
    float outerRadius;             // 외부 반지름
    int segmentCount;              // 세그먼트 개수

    Platform(const glm::vec3& center, float innerRadius, float outerRadius, int segmentCount);

    void update(float delta_time) override; // 플랫폼 업데이트
    void draw(GLint modelLocation) override; // 플랫폼 렌더링
};
