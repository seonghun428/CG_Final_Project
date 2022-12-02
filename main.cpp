#include "Shader.h"
#include "Cube.h"
#include "zombie.h"

#define WINW 800
#define WINH 800

GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Special(int, int, int);
GLvoid Timerfunc(int);

Zombie* zombie = new Zombie();
Cube* plane = new Cube("3DObjects/plane.obj");

BOOL linearproj = false;

BOOL rotate_x = false;
BOOL rotate_y = false;

Shader* shader = new Shader();

GLuint s_program;

GLenum polymode = GL_FILL;

GLfloat rot_x = 0.0f;
GLfloat rot_y = 0.0f;
GLfloat rot_z = 0.0f;

GLfloat move_x = 0.0f;
GLfloat move_y = 0.0f;
GLfloat move_z = 0.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 10.0f);
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	plane->InitBuffer();
	zombie->InitBuffer();

	glEnable(GL_DEPTH_TEST);

	glUseProgram(s_program);

	glm::mat4 projection = glm::mat4(1.0f);
	if (linearproj)
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f); // ���� ����
	else
	{
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));
	}

	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	plane->Render();

	zombie->Move_Update();
	zombie->Render();

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
	shader->InitShader();
	s_program = shader->Get_ShaderID();
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
	case 'p':
	case 'P':
		linearproj = ~linearproj;
		break;

	case 'w':
	case 'W':
		if (polymode != GL_LINE)
			polymode = GL_LINE;
		else
			polymode = GL_FILL;
		break;

	case 'x':
	case 'X':
		rotate_x = ~rotate_x;
		break;

	case 'y':
	case 'Y':
		rotate_y = ~rotate_y;
		break;

	case 's':
	case 'S':
		rotate_x = false;
		rotate_y = false;
		move_x = 0.0f;
		move_y = 0.0f;
		move_z = 0.0f;
		rot_x = 0.0f;
		rot_y = 0.0f;
		rot_z = 0.0f;
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
	switch (key) {
	case GLUT_KEY_UP:
		cameraPos.z += 0.1f;
		break;

	case GLUT_KEY_DOWN:
		cameraPos.z -= 0.1f;
		break;
	}

	glutPostRedisplay();
}

GLvoid Timerfunc(int value)
{
	if (rotate_x)
	{
		rot_x += 5.0f;
	}

	if (rotate_y)
	{
		rot_y += 5.0f;
	}
	
	zombie->Move();

	glutPostRedisplay();
	glutTimerFunc(100, Timerfunc, 1);
}