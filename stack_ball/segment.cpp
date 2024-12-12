#include "segment.h"

Segment::Segment(std::string name) : Object(name) {
    color = glm::vec3(0, 1, 0);
    scale = glm::vec3(0.1, 0.1, 0.1);
}

void Segment::update(float delta_time) {
    Object::update(delta_time); // 부모 클래스의 update() 호출
}

void Segment::draw(GLint modelLocation) {
    // 모델 변환 행렬을 셰이더에 전달
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, obj.size());
}
