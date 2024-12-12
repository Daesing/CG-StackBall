#include "platform.h"

Platform::Platform(const glm::vec3& center, float innerRadius, float outerRadius, int segmentCount)
    : Object(), innerRadius(innerRadius), outerRadius(outerRadius), segmentCount(segmentCount) {
    position = center; // �÷��� �߽� ��ġ ����

    float angleStep = 360.0f / segmentCount; // ���׸�Ʈ �� ���� ����

    for (int i = 0; i < segmentCount; ++i) {
        float angle = glm::radians(i * angleStep);               // ���� ���׸�Ʈ ���� ����
        float nextAngle = glm::radians((i + 1) * angleStep);     // ���� ���׸�Ʈ �� ����
        float midAngle = (angle + nextAngle) / 2.0f;             // ���׸�Ʈ �߽� ����

        // ���׸�Ʈ�� �߽� ��ġ ���
        glm::vec3 segmentPosition(
            center.x - 1.5 * i,
            center.y,
            center.z + 2.0 
        );

        // ���׸�Ʈ ��ü ���� �� ����
        Segment segment("segment.obj");
        
        segment.position = segmentPosition;
        
        if(i!=0)
            segment.rotation.y = -60;

        // ���׸�Ʈ ũ��� ȸ�� ����

        // ���׸�Ʈ�� ����Ʈ�� �߰�
        segments.push_back(segment);
    }
}

void Platform::update(float delta_time) {
    // �θ� Ŭ������ ������Ʈ ���� ȣ�� (ȸ��, �̵� ��)
    Object::update(delta_time);

    // �� ���׸�Ʈ ������Ʈ
    for (auto& segment : segments) {
        segment.update(delta_time);
    }
}

void Platform::draw(GLint modelLocation) {
    // �θ� Ŭ������ ������ ���� ȣ�� (�ʿ��� ���)
    Object::draw(modelLocation);

    // ��� ���׸�Ʈ�� ������
    /*for (auto& segment : segments) {
        segment.draw(modelLocation);
    }*/
    segments[0].draw(modelLocation);
    segments[1].draw(modelLocation);
}
