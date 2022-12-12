#include "scene.h"

#define WINW 800
#define WINH 800

#define ESCAPE 27

CScene scene;

GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Special(int, int, int);
GLvoid Timerfunc(int);
GLvoid Timer2(int);

GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

	scene.Render();

	glutSwapBuffers();
}

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINW, WINH);
	glutCreateWindow("컴퓨터 그래픽스 TEST");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();
	
	// scene.Init_Main();
	scene.Init_Begin();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutTimerFunc(100, Timerfunc, 1);
	glutTimerFunc(1000, Timer2, 2);
	glutMainLoop();

	return 0;
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (key == ESCAPE)
		exit(0);

	if (scene.Get_state() == BEGIN && key == 13)
		scene.Init_Main();

	scene.Input(key);

	glutPostRedisplay();
}

GLvoid Special(int key, int x, int y)
{
	scene.Input_s(key);

	glutPostRedisplay();
}

GLvoid Timerfunc(int value)
{
	scene.Update();

	glutPostRedisplay();
	glutTimerFunc(100, Timerfunc, 1);
}

GLvoid Timer2(int value)
{
	scene.Update2();

	glutPostRedisplay();
	glutTimerFunc(1000, Timer2, 2);
}