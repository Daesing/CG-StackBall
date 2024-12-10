#include "ball.h"

// 생성자: 초기화
Ball::Ball(std::string name):
      Object(name),
      velocity(0.0f, 4.0f, 0.0f),
      gravity(-20.0f),   // 중력 가속도
      elasticity(1.0f),  // 완전 탄성 충돌
      groundLevel(0.0f),
      initialVelocity(10.0f) // 초기 속도 설정
{
    color = glm::vec3(1.0f, 0.0f, 0.0f);    // 공의 색상
    position = glm::vec3(0.0f, 4.0f, 0.0f); // 초기 위치
}

// 공 업데이트
void Ball::update(float delta_time) {
    // 속도와 위치 업데이트
    velocity.y += gravity * delta_time;       // 중력으로 인한 속도 변화
    position.y += velocity.y * delta_time;   // 속도로 위치 변화

    // 바닥에 충돌하면 튕기기
    if (position.y <= groundLevel) {
        position.y = groundLevel;           // 바닥에 위치 고정
        velocity.y = initialVelocity;       // 초기 속도로 반전
    }

    Object::update(delta_time);
}
