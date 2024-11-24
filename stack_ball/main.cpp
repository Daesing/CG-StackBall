#include "global.h"

float cube[6][4][3]{
    { {-0.2,-0.2,0},{0.2,-0.2,0},{-0.2,0.2,0},{0.2,0.2,0} },
    { {-0.2,-0.2,-0.2},{0.2,-0.2,-0.2},{-0.2,0.2,-0.2 },{0.2,0.2,-0.2} },
    { {0.2,-0.2,0},{0.2,-0.2,-0.2},{0.2,0.2,0},{0.2,0.2,-0.2} },
    { {-0.2,-0.2,0},{-0.2,-0.2,-0.2},{-0.2,0.2,0},{-0.2,0.2,-0.2} },
    { {-0.2,-0.2,0},{-0.2,-0.2,-0.2},{0.2,-0.2,0},{0.2,-0.2,-0.2} },
    { {-0.2,0.2,0},{-0.2,0.2,-0.2},{0.2,0.2,0},{0.2,0.2,-0.2} }
};

float cube_colors[3][4][3]{
    { {0,0,1},{0,0,1},{0,0,1},{0,0,1} },
    { {0,1,0},{0,1,0},{0,1,0},{0,1,0} },
    { {1,0,0},{1,0,0},{1,0,0},{1,0,0} }
};

GLuint vao, vbo[2];
GLchar* vertexSource, * fragmentSource;
GLuint vertexShader, fragmentShader;
GLuint shaderProgramID;
GLuint shaderProgramID1;

float line[3][2][3]{
    { {-1,0,0},{1,0,0} },
    { {0,-1,0},{0,1,0} },
    { {0,0,-1},{0,0,1} }
};
float line_colors[3][2][3]{
    { {0,0,1},{0,0,1}},
    { {0,1,0},{0,1,0}},
    { {1,0,0},{1,0,0}}
};

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Example1");
    glewExperimental = GL_TRUE;
    glewInit();
    make_shaderProgram();
    InitBuffer();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(60, TimerFunction, 1);
    glutMainLoop();
}
