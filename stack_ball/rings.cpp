#include "rings.h"
#include <cstdlib>
#include <ctime>
#include "func.h"

Rings::Rings(int count) {
    for (int i = 0; i < count; ++i) {
        Ring ring;
        rings.push_back(ring);
    }
    stack_rings();
}

void Rings::update(float delta_time, bool mouse_state, glm::vec3 ball_pos,int& crushed_stack) {
    bool gameReset = false; // ���� �ʱ�ȭ �÷���

    for (Ring& ring : rings) {
        if (mouse_state) {
            ring.position.y = 5;
            ring.break_ring(delta_time, ball_pos, crushed_stack); // Ŭ�� �� ó��
        }
        else {
            ring.position.y = 0;
        }
        ring.update(delta_time);
    }

    // �μ��� �� ���� �� �߰�
    for (auto it = rings.begin(); it != rings.end();) {
        if (it->broken && it->destroyed) {
            it = rings.erase(it); // �μ��� �� ����
        }
        else {
            ++it;
        }
    }

    // ���� �����ϸ� �߰�
    while (rings.size() < 10) {
        add_ring();
        ++crushed_stack;
        std::cout << "score: "<<crushed_stack << '\n';
        set_level(crushed_stack);
    }
    
}


void Rings::stack_rings() {
    float baseHeight = 0.0f;
    for (int i = 0; i < rings.size(); ++i) {
        for (int j = 0; j < rings[i].ring.size(); ++j) {
            rings[i].ring[j].position.y = baseHeight - i;
            rings[i].ring[j].rotation.y = baseHeight + i * 3;
        }
    }
}

void Rings::draw(GLint modelLocation)
{
    for (Ring& ring : rings) {
        ring.draw(modelLocation);
    }
}

void Rings::buffer()
{
    for (Ring& ring : rings) {
        ring.buffer();
    }
}

void Rings::add_ring()
{
    Ring ring;
    rings.push_back(ring);

    // ���� �߰��� ���� ����
    int newIndex = rings.size() - 1;
    for (int j = 0; j < rings[newIndex].ring.size(); ++j) {
        rings[newIndex].ring[j].position.y = rings[newIndex-1].ring[j].position.y - 1;
        rings[newIndex].ring[j].rotation.y = rings[newIndex - 1].ring[j].rotation.y +  newIndex - 1* 3;
    }

    rings.back().rotation = rings.front().rotation;
    

    rings.back().buffer(); // ���� �߰��� ���� ���۸�
}


void Rings::set_pos()
{   
	for (int i = 0; i < rings.size(); ++i) {
		for (int j = 0; j < rings[i].ring.size(); ++j) {
            rings[i].ring[j].position.y += 0.5;
		}
	}
}

void Rings::set_level(int& score)
{
    if (score % 20 == 0) {
        ++level;
        std::cout << "Level up Now at Level " << level << '\n';
        increase_rotation();
        
    }
}

void Rings::increase_rotation()
{
    for (Ring& ring : rings) {
        ring.rotation += 10;
    }
    std::cout << "current_speed: " << rings.back().rotation << '\n';
}



