#include "ring.h"
#include "func.h"

std::uniform_int_distribution uid{ 0,5 };

Ring::Ring() {
    for (int i = 1; i <= 6; ++i) {
        std::string fileName = "segment" + std::to_string(i) + ".obj";
        Segment segment(fileName);
        ring.push_back(segment);
    }
    ring[uid(dre)].color.b = 1.0f;
}

void Ring::update(float delta_time) {
    int cnt = 0;  // ���׸�Ʈ ī��Ʈ

    // ���� ���� ��� ���׸�Ʈ�� ������Ʈ
    for (Segment& segment : ring) {
        if (broken) {
            // ���׸�Ʈ ��ġ ����
            segment.position.y += delta_time * 3.0f;
            switch (cnt) {
            case 0: segment.position.x -= delta_time * 3.0f; break;
            case 1: segment.position.x -= delta_time * 5.0f; break;
            case 2: segment.position.x += delta_time * 3.0f; break;
            case 3: segment.position.x += delta_time * 5.0f; break;
            case 4: segment.position.x += delta_time * 4.0f; break;
            case 5: segment.position.x -= delta_time * 4.0f; break;
            default: break;
            }
        }

        // ���׸�Ʈ�� ���� ��ġ�� ������ ���� ��� �÷��� ����
        if (segment.position.y > 4) {
            destroyed = true;
        }

        // ȸ���� ������Ʈ ����
        segment.rotation.y += 80 * delta_time;
        segment.update(delta_time);
        ++cnt;
    }
}

void Ring::buffer()
{
    for (Segment& segment : ring) {
        InitBuffer(segment);
    }
}

void Ring::draw(GLint modelLocation)
{
    for (Segment& segment : ring) {
        segment.draw(modelLocation);
    }
}

void Ring::break_ring(float delta_time, glm::vec3 ball_pos, bool& gameReset) {
    for (Segment& segment : ring) {
        // �浹 �˻�
        if (glm::abs(segment.position.y - ball_pos.y) <= 1.0f) {
            // Ư�� ������ ��� ���� �μ�
            if (segment.color == glm::vec3(0, 1, 1)) {
                broken = true;
                break;
            }
            else {
                // �ٸ� ������ ��ϰ� �浹�ϸ� ���� �ʱ�ȭ
                //gameReset = true;
                return;
            }
        }
    }
}

