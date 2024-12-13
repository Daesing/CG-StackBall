#include "object.h"

class Ball : public Object {
public:
    bool descending{ true };
    glm::vec3 velocity; // ���� �ӵ�
    float gravity;      // �߷� ���ӵ�
    float elasticity;   // ź�� ���
    float groundLevel;  // �ٴ� ��ġ
    float initialVelocity;
    bool is_fall{ false };
    Ball(std::string name);

    void update(float deltaTime) override;

};

