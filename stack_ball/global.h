#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h>							//--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

extern std::default_random_engine dre;
extern std::random_device rd;

extern GLuint shaderProgramID; //--- ���̴� ���α׷� �̸�
extern glm::vec3 cameraPos;