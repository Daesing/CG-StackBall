#define _CRT_SECURE_NO_WARNINGS
#include "global.h"
#include "object.h"
#include "ball.h"
#include "cylinder.h"
#include "segment.h"
#include "ring.h"
#define Width 800
#define Height 600

std::random_device seeder;
const auto seed = seeder.entropy() ? seeder() : time(nullptr);
std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
std::uniform_real_distribution<double> dist(0, 1.0f);

std::random_device seeder2;
const auto seed2 = seeder2.entropy() ? seeder2() : time(nullptr);
std::mt19937 ge(static_cast<std::mt19937::result_type>(seed2));
std::uniform_real_distribution<double> dis(-0.9, 0.9);



Ball sphere("sphere.obj");
Cylinder pillar("cylinder.obj");
Segment segment("segment.obj");
Ring ring("ring.obj");

Segment segments[6] = {
	Segment("segment.obj"),
	Segment("segment.obj"),
	Segment("segment.obj"),
	Segment("segment.obj"),
	Segment("segment.obj"),
	Segment("segment.obj"),
};

GLvoid InitBuffer(Object&);
char* filetobuf(const char* file);
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
GLvoid drawScene();
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);


GLint width, height;
GLuint shaderProgramID; //--- 세이더 프로그램 이름
GLuint vertexShader; //--- 버텍스 세이더 객체
GLuint fragmentShader; //--- 프래그먼트 세이더 객체
GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLint modelLocation, viewLocation, projectionLocation;


// 초기화 함수에서 유니폼 위치를 가져옵니다.
void initializeUniformLocations(GLuint shaderProgramID, GLint& modelLocation, GLint& viewLocation, GLint& projectionLocation) {
	modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");
	viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
	projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");

	if (modelLocation == -1 || viewLocation == -1 || projectionLocation == -1) {
		std::cerr << "Failed to find uniform locations!" << std::endl;
	}
}

void initializeShaderUniforms() {
	initializeUniformLocations(shaderProgramID, modelLocation, viewLocation, projectionLocation);
}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();
	make_shaderProgram();
	InitBuffer(sphere);
	InitBuffer(pillar);
	InitBuffer(segment);
	InitBuffer(ring);
	initializeShaderUniforms();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(15,TimerFunction,1);
	
	glutMainLoop();
}


void drawScene() {
	GLfloat rColor, gColor, bColor;
	rColor = bColor = 1.0f;
	gColor = 1.0f;

	// 배경 초기화
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// 셰이더 활성화
	glUseProgram(shaderProgramID);

	// 카메라 설정
	glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 6.0f);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

	// 투영 변환 설정
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.4f, 50.0f);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	// 객체 렌더링
	sphere.draw(modelLocation);
	pillar.draw(modelLocation);
	//segment.draw(modelLocation);
	ring.draw(modelLocation);

	// 화면 출력
	glutSwapBuffers();
}


void InitBuffer(Object& input)
{
	glGenVertexArrays(1, &input.vao); // VAO 생성
	glBindVertexArray(input.vao);

	for (int i = 1; i < input.obj.size(); i += 2) {
		input.obj[i] = input.color;
	}

	// 데이터 분리: 정점 및 색상
	std::vector<glm::vec3> vertices, colors;
	for (size_t i = 0; i < input.obj.size(); i += 2) {
		vertices.push_back(input.obj[i]);     // 정점
		colors.push_back(input.obj[i + 1]);  // 색상
	}

	glGenBuffers(2, input.vbo); // 두 개의 VBO 생성

	// 1. 정점 데이터 VBO
	glBindBuffer(GL_ARRAY_BUFFER, input.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// 2. 색상 데이터 VBO
	glBindBuffer(GL_ARRAY_BUFFER, input.vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

//--- 버텍스 세이더 객체 만들기
void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

//--- 프래그먼트 세이더 객체 만들기
void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentShader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}

}

//--- 세이더 프로그램 만들고 세이더 객체 링크하기
void make_shaderProgram()
{
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
	glUseProgram(shaderProgramID);

}

//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수	
{
	glViewport(0, 0, w, h);
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}




GLvoid Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
}

//Timer ball animation
GLvoid TimerFunction(int value) {

	static float last_time = 0.0f;
	float current_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // 초 단위
	float delta_time = current_time - last_time;
	last_time = current_time;

	sphere.update(delta_time); // 공 상태 업데이트
	pillar.update(delta_time);
	segment.update(delta_time);
	ring.update(delta_time);

	glutTimerFunc(16, TimerFunction, 1);
	glutPostRedisplay();


}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		sphere.is_fall = true;
		sphere.position.y = 1.0f;
	}
	else {
		sphere.is_fall = false;
	}

}


