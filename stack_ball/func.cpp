#include "func.h"

void InitBuffer(Object& input)
{
	glGenVertexArrays(1, &input.vao); // VAO ����
	glBindVertexArray(input.vao);

	for (int i = 1; i < input.obj.size(); i += 2) {
		input.obj[i] = input.color;
	}

	// ������ �и�: ���� �� ����
	std::vector<glm::vec3> vertices, colors;
	for (size_t i = 0; i < input.obj.size(); i += 2) {
		vertices.push_back(input.obj[i]);     // ����
		colors.push_back(input.obj[i + 1]);  // ����
	}

	glGenBuffers(2, input.vbo); // �� ���� VBO ����

	// 1. ���� ������ VBO
	glBindBuffer(GL_ARRAY_BUFFER, input.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// 2. ���� ������ VBO
	glBindBuffer(GL_ARRAY_BUFFER, input.vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}