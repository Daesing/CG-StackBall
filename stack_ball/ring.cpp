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
            case 0: 
                segment.position.x -= delta_time * 3.0f; 
                segment.rotation.z += delta_time * 60;
                break;
            case 1: 
                segment.position.x -= delta_time * 5.0f;
                segment.rotation.z += delta_time * 60;
                break;
            case 2: 
                segment.position.x += delta_time * 3.0f; 
                segment.rotation.z -= delta_time * 60;
                break;
            case 3: 
                segment.position.x += delta_time * 5.0f;
                segment.rotation.z += delta_time * 60;
                break;
            case 4: 
                segment.position.x += delta_time * 4.0f;
                segment.rotation.z -= delta_time * 60; 
                break;
            case 5: 
                segment.position.x -= delta_time * 4.0f;
                segment.rotation.z += delta_time * 60;
                break;
            default: break;
            }
        }

        // ���׸�Ʈ�� ���� ��ġ�� ������ ���� ��� �÷��� ����
        if (segment.position.y > 4) {
            destroyed = true;
        }

        // ȸ���� ������Ʈ ����
        segment.position += position * delta_time;
        segment.rotation.y += rotation * delta_time;
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

void Ring::break_ring(float delta_time, glm::vec3 ball_pos,int& score) {
    for (Segment& segment : ring) {
        // �浹 �˻�
        if (glm::abs(segment.position.x - ball_pos.x) <= 0.1f &&  // X�� �浹 ����
            glm::abs(segment.position.y - ball_pos.y) <= 1.0f) { // Y�� �浹 ����

            if (fabs(segment.color.g - 1.0f) < 0.0001f && fabs(segment.color.b - 1.0f) < 0.0001f) {
                broken = true;
                std::cout << "color.g: " << segment.color.g << ", color.b: " << segment.color.b << std::endl;
                return; // �� �̻� Ȯ���� �ʿ� ����
            }

        }
    }
}


