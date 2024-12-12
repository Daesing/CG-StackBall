#pragma once

#include "object.h"
#include "segment.h"
#include <vector>

class Platform : public Object {
public:
    std::vector<Segment> segments; // �÷����� �����ϴ� ���׸�Ʈ��
    float innerRadius;             // �߽� ���� ������
    float outerRadius;             // �ܺ� ������
    int segmentCount;              // ���׸�Ʈ ����

    Platform(const glm::vec3& center, float innerRadius, float outerRadius, int segmentCount);

    void update(float delta_time) override; // �÷��� ������Ʈ
    void draw(GLint modelLocation) override; // �÷��� ������
};
