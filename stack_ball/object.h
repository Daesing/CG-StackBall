#pragma once
#include "global.h"

class Object {
public:
	GLuint vao, vbo[2];
	std::vector<glm::vec3> obj;
	glm::mat4 matrix = glm::mat4(1.0f);
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 position = glm::vec3(0.0f);
	float angle;
	glm::vec3 scale = glm::vec3(1.0f);

	Object(std::string name);
	virtual ~Object() = default; 
	
	virtual void update(float);
	
	void draw(GLint);

};


std::vector<glm::vec3> ReadObj(const std::string& filename);