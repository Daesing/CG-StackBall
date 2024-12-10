#include "object.h"

class Ball : public Object {
public:
    bool descending{ true };
    glm::vec3 velocity; // ���� �ӵ�
    float gravity;      // �߷� ���ӵ�
    float elasticity;   // ź�� ���
    float groundLevel;  // �ٴ� ��ġ
    float initialVelocity;
    Ball(std::string name);

    void update_ball(float deltaTime);

};

