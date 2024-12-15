#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h>							//--- 필요한 헤더파일 include
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

extern GLuint shaderProgramID; //--- 세이더 프로그램 이름
extern glm::vec3 cameraPos;