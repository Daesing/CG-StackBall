#include "object.h"
#include "func.h"

Object::Object(std::string name) {
	obj = ReadObj(name);
	std::cout << "object: " << name << '\n';
}

void Object::update(float)
{
	// 모델 변환 행렬 갱신
	matrix = glm::mat4(1.0f);               // 행렬 초기화
	matrix = glm::translate(matrix, position); // 새로운 위치로 이동
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, scale);
	change_color(color);
}

void Object::draw(GLint modelLocation) {
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, obj.size());
}

void Object::change_color(glm::vec3 color)
{
	for (size_t i = 0; i < obj.size(); i += 9) { // Iterate every 9 floats (one vertex)
		obj[i + 6] = color.x; // Update red channel
		obj[i + 7] = color.y; // Update green channel
		obj[i + 8] = color.z; // Update blue channel
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, obj.size() * sizeof(float), &obj[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


//ReadObj
std::vector<float> ReadObj(const std::string& filename) {
	std::ifstream in{ filename };
	if (!in) {
		std::cerr << filename << " file read failed\n";
		exit(1);
	}

	std::vector<glm::vec3> vertex;       // Vertex positions
	std::vector<glm::vec3> normal;       // Vertex normals
	std::vector<glm::ivec3> index;       // Face indices (vertex)
	std::vector<glm::ivec3> normalIndex; // Face indices (normal)
	std::vector<float> data;             // Interleaved data for OpenGL

	glm::vec3 defaultNormal(0.0f, 0.0f, 1.0f);

	while (in) {
		std::string line;
		std::getline(in, line);
		std::stringstream ss(line);
		std::string type;
		ss >> type;

		if (type == "v") {
			glm::vec3 v;
			ss >> v.x >> v.y >> v.z;
			vertex.push_back(v);
		}
		else if (type == "vn") {
			glm::vec3 vn;
			ss >> vn.x >> vn.y >> vn.z;
			normal.push_back(vn);
		}
		else if (type == "f") {
			std::vector<int> face;            // 정점 인덱스 저장
			std::vector<int> faceNormal;      // 법선 인덱스 저장
			std::string token;

			while (ss >> token) {
				std::stringstream tokenStream(token);
				std::string vIdx, nIdx;

				std::getline(tokenStream, vIdx, '/'); // 정점 인덱스
				tokenStream.ignore(std::numeric_limits<std::streamsize>::max(), '/'); // 텍스처 좌표 무시
				std::getline(tokenStream, nIdx, '/'); // 법선 인덱스

				face.push_back(std::stoi(vIdx) - 1);
				faceNormal.push_back(nIdx.empty() ? -1 : (std::stoi(nIdx) - 1));
			}

			// 삼각형으로 분할
			for (size_t i = 1; i < face.size() - 1; ++i) {
				index.push_back(glm::ivec3(face[0], face[i], face[i + 1]));
				normalIndex.push_back(glm::ivec3(faceNormal[0], faceNormal[i], faceNormal[i + 1]));
			}
		}

	}
	// Combine vertex and normal data into a single array
	for (size_t i = 0; i < index.size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			int vIdx = index[i][j];
			int nIdx = normalIndex[i][j];

			// Add vertex position
			if (vIdx >= 0 && vIdx < vertex.size()) {
				data.push_back(vertex[vIdx].x);
				data.push_back(vertex[vIdx].y);
				data.push_back(vertex[vIdx].z);
			}
			else {
				std::cerr << "Invalid vertex index: " << vIdx << "\n";
				data.push_back(0.0f); // Fallback
				data.push_back(0.0f);
				data.push_back(0.0f);
			}

			// Add normal
			if (nIdx >= 0 && nIdx < normal.size()) {
				data.push_back(normal[nIdx].x);
				data.push_back(normal[nIdx].y);
				data.push_back(normal[nIdx].z);
			}
			else {
				data.push_back(defaultNormal.x);
				data.push_back(defaultNormal.y);
				data.push_back(defaultNormal.z);
			}

			// Add random color
			data.push_back(0);
			data.push_back(0);
			data.push_back(0);
		}
	}

	std::cout << filename << " File Read, " << index.size() << " Faces (" << data.size() / 9 << " Vertices) Exists." << std::endl;
	return data;
}

