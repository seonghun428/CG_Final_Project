#define _CRT_SECURE_NO_WARNINGS

#include "header.h"

#define WINW 800
#define WINH 800

GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Special(int, int, int);
GLvoid Timerfunc(int);

BOOL linearproj = false;

GLfloat win2gl(int num, char dir)
{
	switch (dir)
	{
	case 'x':
		return (GLfloat)(num - WINW / 2) / (WINW / 2);
		break;
	case 'y':
		return (GLfloat)(num - WINH / 2) / -(WINH / 2);
		break;
	}
}

int gl2win(GLfloat num, char dir)
{
	switch (dir)
	{
	case 'x':
		return (int)(num * (WINW / 2) + (WINW / 2));
		break;
	case 'y':
		return (int)(num * -(WINH / 2) + (WINH / 2));
		break;
	}
}

GLchar* vertexsource, * fragmentsource; //--- 소스코드 저장 변수
GLuint vertexshader, fragmentshader; //--- 세이더 객체

glm::vec3* cube;

GLfloat cube_color[8][3] = {
	{ 1.0f, 0.0f, 1.0f }
	,{ 1.0f, 1.0f, 1.0f }
	,{ 0.0f, 0.0f, 1.0f }
	,{ 0.0f, 1.0f, 1.0f }
	,{ 1.0f, 0.0f, 0.0f }
	,{ 1.0f, 1.0f, 0.0f }
	,{ 0.0f, 0.0f, 0.0f }
	,{ 0.0f, 1.0f, 0.0f }
};

unsigned int cube_index[6][6] = {
		{0,1,4
		,5,1,4}

		,{2,3,6
		,7,3,6}

		,{0,1,2
		,3,1,2}

		,{4,5,6
		,7,5,6}

		,{0,2,4
		,6,2,4}

		,{1,3,5
		,7,3,5}
};

char* filetobuf(const char* file)
{
	std::string code;
	std::ifstream fin(file, std::ios::in);
	if (fin.is_open())
	{
		std::string Line = "";
		while (getline(fin, Line))
			code += "\n" + Line;
		fin.close();
	}
	else
		return 0;
	char* buf = new char[code.length() + 1];
	strcpy(buf, code.c_str());
	return buf;
}

int vertexNum;
int faceNum;
int vertIndex;
int faceIndex;

void ReadObj(const char* objFile)
{
	FILE* fptr;
	fptr = fopen(objFile, "rb");
	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기
	char count[100];
	char bind[100];

	vertexNum = 0;
	faceNum = 0;

	while (!feof(fptr)) {
		fscanf(fptr, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexNum += 1;
		else if (count[0] == 'f' && count[1] == '\0')
			faceNum += 1;
		memset(count, '\0', sizeof(count)); // 배열 초기화
	}

	fseek(fptr, 0, SEEK_SET);

	//--- 2. 메모리 할당
	glm::vec4* vertex = new glm::vec4[vertexNum];
	glm::vec4* face = new glm::vec4[faceNum];

	cube = new glm::vec3[vertexNum];

	vertIndex = 0;
	faceIndex = 0;

	//--- 3. 할당된 메모리에 각 버텍스, 페이스 정보 입력
	while (!feof(fptr)) {
		fscanf(fptr, "%s", bind);
		if (bind[0] == 'v' && bind[1] == '\0') {
			fscanf(fptr, "%f %f %f", &vertex[vertIndex].x, &vertex[vertIndex].y, &vertex[vertIndex].z);
			vertIndex++;
		}
		else if (bind[0] == 'f' && bind[1] == '\0') {
			fscanf(fptr, "%f %f %f", &face[faceIndex].x, &face[faceIndex].y, &face[faceIndex].z);
			faceIndex++;
		}
	}

	fclose(fptr);

	for (int i = 0; i < vertIndex; ++i)
		{
			cube[i] = vertex[i];
		}

	delete[] vertex, face;
}

void make_vertexShader()
{
	vertexsource = filetobuf("vertex.glsl");
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	glCompileShader(vertexshader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShader()
{
	fragmentsource = filetobuf("fragment.glsl");
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	glCompileShader(fragmentshader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

GLuint s_program;

void InitShader()
{
	make_vertexShader(); //--- 버텍스 세이더 만들기
	make_fragmentShader(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	s_program = glCreateProgram();
	glAttachShader(s_program, vertexshader);
	glAttachShader(s_program, fragmentshader);
	glLinkProgram(s_program);

	//--- 세이더 삭제하기
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	//--- Shader Program 사용하기
	glUseProgram(s_program);
}

GLuint vao_cube, vbo_cube[2], ebo_cube;

void InitBuffer()
{
	glGenVertexArrays(1, &vao_cube);
	glBindVertexArray(vao_cube);
	glGenBuffers(2, vbo_cube);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube[0]);
	glBufferData(GL_ARRAY_BUFFER, _msize(cube), cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &ebo_cube);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_cube);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_color), cube_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	delete[] cube;
}

GLenum polymode = GL_FILL;

float rot_x = 0.0f;
float rot_y = 0.0f;
float rot_z = 0.0f;

double move_x = 0.0f;
double move_y = 0.0f;
double move_z = 0.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ReadObj("cube.obj");

	InitBuffer();

	glUseProgram(s_program);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, polymode);

	glm::mat4 projection = glm::mat4(1.0f);
	if (linearproj)
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f); // 직각 투영
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

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Txr = glm::mat4(1.0f); //--- 역이동 행렬 선언
	glm::mat4 Rt = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 Rx = glm::mat4(1.0f); //--- x축 회전 행렬 선언
	glm::mat4 Ry = glm::mat4(1.0f); //--- y축 회전 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- z축 회전 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬
	Tx = glm::translate(Tx, glm::vec3(move_x, move_y, move_z)); //--- 이동 행렬
	Txr = glm::translate(Txr, glm::vec3(-move_x, -move_y, -move_z)); //--- 역이동 행렬
	Rx = glm::rotate(Rx, glm::radians(rot_x), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	Ry = glm::rotate(Ry, glm::radians(rot_y), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	Rz = glm::rotate(Rz, glm::radians(rot_z), glm::vec3(0.0, 0.0, 1.0)); //--- z축에 대하여 회전 행렬
	Rt = Rx * Ry * Rz;
	TR = Txr * Rt * Tx;

	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));

	glBindVertexArray(vao_cube);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	glutSwapBuffers();
}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
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
	InitShader();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutTimerFunc(100, Timerfunc, 1);
	glutMainLoop();
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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

	case 'q':
	case 'Q':
		exit(0);
		break;
	}

	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}

GLvoid Special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		cameraPos.z += 0.1;
		break;

	case GLUT_KEY_DOWN:
		cameraPos.z -= 0.1;
		break;
	}

	glutPostRedisplay();
}

GLvoid Timerfunc(int value)
{
	

	glutPostRedisplay();
	glutTimerFunc(100, Timerfunc, 1);
}