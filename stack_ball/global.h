#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glm/gtc/type_ptr.hpp>
#include "func.h"
#include "ball.h"

extern float line[3][2][3];
extern float line_colors[3][2][3];

extern GLuint vao, vbo[2];
extern GLchar* vertexSource, * fragmentSource;
extern GLuint vertexShader, fragmentShader;
extern GLuint shaderProgramID;
extern GLuint shaderProgramID1;

extern glm::mat4 projection;
extern glm::mat4 view;
extern Ball ball;
