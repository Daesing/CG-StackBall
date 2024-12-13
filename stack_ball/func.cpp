#include "func.h"

void InitBuffer(Object& input)
{
	glGenVertexArrays(1, &input.vao);
	glGenBuffers(1, input.vbo);

	glBindVertexArray(input.vao);
	glBindBuffer(GL_ARRAY_BUFFER, input.vbo[0]);

	// 업로드 데이터는 float 배열로 전달
	glBufferData(GL_ARRAY_BUFFER, input.obj.size() * sizeof(float), &input.obj[0], GL_STATIC_DRAW);

	// Vertex Attributes 설정 (Vertex, Normal, Color)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0); // Position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float))); // Normal
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float))); // Color
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	glUseProgram(shaderProgramID);
	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
	glUniform3f(lightPosLocation, 0.0, 3.0, 5.0);
	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
}