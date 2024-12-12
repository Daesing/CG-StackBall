#include "platform.h"

Platform::Platform(const glm::vec3& center, float innerRadius, float outerRadius, int segmentCount)
    : Object(), innerRadius(innerRadius), outerRadius(outerRadius), segmentCount(segmentCount) {
    position = center; // 플랫폼 중심 위치 설정

    float angleStep = 360.0f / segmentCount; // 세그먼트 간 각도 간격

    for (int i = 0; i < segmentCount; ++i) {
        float angle = glm::radians(i * angleStep);               // 현재 세그먼트 시작 각도
        float nextAngle = glm::radians((i + 1) * angleStep);     // 다음 세그먼트 끝 각도
        float midAngle = (angle + nextAngle) / 2.0f;             // 세그먼트 중심 각도

        // 세그먼트의 중심 위치 계산
        glm::vec3 segmentPosition(
            center.x - 1.5 * i,
            center.y,
            center.z + 2.0 
        );

        // 세그먼트 객체 생성 및 설정
        Segment segment("segment.obj");
        
        segment.position = segmentPosition;
        
        if(i!=0)
            segment.rotation.y = -60;

        // 세그먼트 크기와 회전 설정

        // 세그먼트를 리스트에 추가
        segments.push_back(segment);
    }
}

void Platform::update(float delta_time) {
    // 부모 클래스의 업데이트 로직 호출 (회전, 이동 등)
    Object::update(delta_time);

    // 각 세그먼트 업데이트
    for (auto& segment : segments) {
        segment.update(delta_time);
    }
}

void Platform::draw(GLint modelLocation) {
    // 부모 클래스의 렌더링 로직 호출 (필요한 경우)
    Object::draw(modelLocation);

    // 모든 세그먼트를 렌더링
    /*for (auto& segment : segments) {
        segment.draw(modelLocation);
    }*/
    segments[0].draw(modelLocation);
    segments[1].draw(modelLocation);
}
