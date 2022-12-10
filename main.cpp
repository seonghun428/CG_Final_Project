#include "scene.h"

#define WINW 800
#define WINH 800

GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Special(int, int, int);
GLvoid Timerfunc(int);

Scene scene;
GLenum polymod = GL_FILL;

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, polymod);

	scene.Render();

	glutSwapBuffers();
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
	
	scene.Init_Main();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutTimerFunc(100, Timerfunc, 1);
	glutMainLoop();

	return 0;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
	case 'W':
		if (polymod == GL_FILL)	polymod = GL_LINE;
		else polymod = GL_FILL;
		break;

	case 'x':
	case 'X':
		break;

	case 'y':
	case 'Y':
		break;

	case 's':
	case 'S':
		break;

	case 'q':
	case 'Q':
		exit(0);
		break;
	}

	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}

GLvoid Special(int key, int x, int y)
{
	/*switch (key) {
	case GLUT_KEY_UP:
		cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
		break;

	case GLUT_KEY_DOWN:
		cameraPos = glm::vec3(0.0f, 0.0f, -5.0f);
		break;

	case GLUT_KEY_LEFT:
		cameraPos = glm::vec3(-10.0f, 0.0f, 0.0f);
		break;

	case GLUT_KEY_RIGHT:
		cameraPos = glm::vec3(10.0f, 0.0f, 0.0f);
		break;
	}*/

	glutPostRedisplay();
}

GLvoid Timerfunc(int value)
{
	

	glutPostRedisplay();
	glutTimerFunc(100, Timerfunc, 1);
}