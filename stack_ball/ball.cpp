#include "ball.h"

// ������: �ʱ�ȭ
Ball::Ball(std::string name):
      Object(name),
      velocity(0.0f, 6.0f, 0.0f),
      gravity(-20.0f),   // �߷� ���ӵ�
      elasticity(1.0f),  // ���� ź�� �浹
      groundLevel(1.0f),
      initialVelocity(6.0f) // �ʱ� �ӵ� ����
{
    color = glm::vec3(1.0f, 0.0f, 0.0f);    // ���� ����
    position = glm::vec3(0.0f, 2.0f, 3.7f); // �ʱ� ��ġ
    scale = glm::vec3(0.5, 0.5, 0.5);
}

// �� ������Ʈ
void Ball::update(float delta_time) {
    // �ӵ��� ��ġ ������Ʈ
    if (!is_fall) {
        velocity.y += gravity * delta_time;       // �߷����� ���� �ӵ� ��ȭ
        position.y += velocity.y * delta_time;   // �ӵ��� ��ġ ��ȭ

        // �ٴڿ� �浹�ϸ� ƨ���
        if (position.y <= groundLevel) {
            position.y = groundLevel;           // �ٴڿ� ��ġ ����
            velocity.y = initialVelocity;       // �ʱ� �ӵ��� ����
        }
    }
    Object::update(delta_time);
}
