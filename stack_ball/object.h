#include "global.h"
class Object {
public:
	GLuint vao, vbo[2];
	std::vector<glm::vec3> obj;
	glm::mat4 matrix = glm::mat4(1.0f);

	Object(std::string name);
	

};


std::vector<glm::vec3> ReadObj(const std::string& filename);