#include "object.h"

Object::Object(std::string name) {
	obj = ReadObj(name);
	std::cout << "object: " << name << '\n';
}

void Object::update(float)
{
	// �� ��ȯ ��� ����
	matrix = glm::mat4(1.0f);               // ��� �ʱ�ȭ
	matrix = glm::translate(matrix, position); // ���ο� ��ġ�� �̵�
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, scale);
}

void Object::draw(GLint modelLocation) {
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, obj.size());
}



//ReadObj
std::vector<glm::vec3> ReadObj(const std::string& filename) {
	std::ifstream in{ filename };
	if (!in) {
		std::cout << filename << " file read failed\n";
		exit(1);
	}
	std::vector<glm::vec3> vertex;
	std::vector<glm::ivec3> index;
	std::vector<glm::ivec2> lineIndex;
	while (in) {
		std::string line;
		std::getline(in, line);
		std::stringstream ss{ line };
		std::string str;
		ss >> str;
		if (str == "v") {
			glm::vec3 v;
			for (int i = 0; i < 3; ++i) {
				std::string subStr;
				ss >> subStr;
				v[i] = std::stof(subStr);
			}
			vertex.push_back(v);
		}
		else if (str == "f") {
			glm::ivec3 f;
			for (int i = 0; i < 3; ++i) {
				std::string substr;
				ss >> substr;
				std::stringstream subss{ substr };
				std::string vIdx;
				std::getline(subss, vIdx, '/');
				f[i] = std::stoi(vIdx) - 1;
			}
			index.push_back(f);
		}
		else if (str == "l") {
			glm::ivec2 l;
			for (int i = 0; i < 2; ++i) {
				std::string substr;
				ss >> substr;
				l[i] = std::stoi(substr) - 1;
			}
			lineIndex.push_back(l);
		}
	}
	std::vector<glm::vec3> data;
	for (auto& f : index) {
		data.push_back(vertex[f[0]]);
		data.push_back(glm::vec3(rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX)));
		data.push_back(vertex[f[1]]);
		data.push_back(glm::vec3(rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX)));
		data.push_back(vertex[f[2]]);
		data.push_back(glm::vec3(rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX)));
	}
	for (auto& l : lineIndex) {
		data.push_back(vertex[l[0]]);
		data.push_back(glm::vec3(rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX)));
		data.push_back(vertex[l[1]]);
		data.push_back(glm::vec3(rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX)));
	}
	std::cout << filename << " File Read, " << data.size() / 2 << " Vertices Exists." << std::endl;
	return data;
}