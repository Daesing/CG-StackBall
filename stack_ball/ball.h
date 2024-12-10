#include "object.h"

class Ball : public Object {
public:
    bool descending{ true };
    glm::vec3 velocity; // 공의 속도
    float gravity;      // 중력 가속도
    float elasticity;   // 탄성 계수
    float groundLevel;  // 바닥 위치
    float initialVelocity;
    Ball(std::string name);

    void update_ball(float deltaTime);

};

