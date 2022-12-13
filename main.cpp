#include "scene.h"

#define WINW 800
#define WINH 800

#define ESCAPE 27
#define ENTER 13

CScene scene;

GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid Special(int, int, int);
GLvoid Timerfunc(int);
GLvoid Timer2(int);

GLvoid drawScene()
{
	scene.Render();
}

int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINW, WINH);
	glutCreateWindow("��ǻ�� �׷��Ƚ� TEST");

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();
	
	scene.shader.InitShader();
	scene.Init_Textures();
	scene.Init_Begin();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutSpecialFunc(Special);
	glutTimerFunc(100, Timerfunc, 1);
	glutTimerFunc(1000, Timer2, 2);
	glutMainLoop();

	return 0;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (key == ESCAPE)
		exit(0);

	if (scene.Get_state() == BEGIN && key == ENTER)
		scene.Init_Main();

	else if (scene.Get_state() == MAIN && key == ENTER)
		scene.Init_Lose();

	else if (scene.Get_state() == LOSE && key == ENTER)
		scene.Init_Begin();

	scene.Input(key);

	glutPostRedisplay();
}

GLvoid Special(int key, int x, int y)
{
	scene.Input_s(key);

	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int mx, int my)
{
	scene.mouse(button, state, mx, my);

	glutPostRedisplay();
}

GLvoid Timerfunc(int value)
{
	scene.Update();

	glutPostRedisplay();
	glutTimerFunc(50, Timerfunc, 1);
}

GLvoid Timer2(int value)
{
	scene.Update2();

	glutPostRedisplay();
	glutTimerFunc(100, Timer2, 2);
}