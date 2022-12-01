#include "header.h"
#include "Shader.h"

#define WINW 800
#define WINH 800

GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Special(int, int, int);
GLvoid Timerfunc(int);

BOOL linearproj = false;

BOOL rotate_x = false;
BOOL rotate_y = false;

Shader* shader = new Shader();

GLfloat lines[6][3] = {
	{ -1.0f, 0.0f, 0.0f }
	,{ 1.0f, 0.0f, 0.0f }
	,{ 0.0f, -1.0f, 0.0f }
	,{ 0.0f, 1.0f, 0.0f }
	,{ 0.0f, 0.0f, -1.0f }
	,{ 0.0f, 0.0f, 1.0f }
};

GLfloat lines_color[6][3] = {
	{ 1.0f, 0.0f, 0.0f }
	,{ 1.0f, 0.0f, 0.0f }
	,{ 0.0f, 1.0f, 0.0f }
	,{ 0.0f, 1.0f, 0.0f }
	,{ 0.0f, 0.0f, 1.0f }
	,{ 0.0f, 0.0f, 1.0f }
};

vector<glm::vec3> m_outvertex;
vector<glm::vec3> m_outnormal;
vector<glm::vec2> m_outuv;

GLint m_Tri_Num;

void ReadObj(const char* objFile)
{
	GLfloat sumX = 0.0f, sumY = 0.0f, sumZ = 0.0f;
	GLfloat avgX, avgY, avgZ;
	GLfloat scaleX, scaleY, scaleZ;
	GLfloat minX = 0.0f, minY = 0.0f, minZ = 0.0f;
	GLfloat maxX = 0.0f, maxY = 0.0f, maxZ = 0.0f;

	vector<glm::vec3> temp_vertices;
	vector<glm::vec3> temp_normals;
	vector<glm::vec2> temp_uvs;

	vector<unsigned int> vertexIndices, normalIndices, uvIndices;

	ifstream fin{ objFile };
	static int i = 0;
	if (!fin)
	{
		cerr << " File Open Failed" << endl;
		exit(-1);
	}
	else
	{
		char line[512];
		char face[512];
		while (!fin.eof()) {
			fin >> line;

			if (line[0] == 'v' && line[1] == '\0') {
				glm::vec3 vertex;
				fin >> vertex.x >> vertex.y >> vertex.z;
				if (vertex.x < minX) minX = vertex.x;
				if (vertex.y < minY) minY = vertex.y;
				if (vertex.z < minZ) minZ = vertex.z;
				if (vertex.x > maxX) maxX = vertex.x;
				if (vertex.y > maxY) maxY = vertex.y;
				if (vertex.z > maxZ) maxZ = vertex.z;
				sumX += vertex.x;
				sumY += vertex.y;
				sumZ += vertex.z;

				temp_vertices.push_back(vertex);
			}

			else if (line[0] == 'v' && line[1] == 't') {
				glm::vec2 uv;
				fin >> uv.x >> uv.y;
				temp_uvs.push_back(uv);
			}

			else if (line[0] == 'v' && line[1] == 'n') {
				glm::vec3 normal;
				fin >> normal.x >> normal.y >> normal.z;
				temp_normals.push_back(normal);
			}

			else if (line[0] == 'f' && line[1] == '\0') {
				string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

				for (int i = 0; i < 3; ++i)
				{
					memset(face, 0, sizeof(face));
					fin >> face;

					vertexIndex[i] = atoi(strtok(face, "/"));
					uvIndex[i] = atoi(strtok(NULL, "/"));
					normalIndex[i] = atoi(strtok(NULL, "/"));
				}

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		fin.close();
	}

	avgX = sumX / vertexIndices.size();
	avgY = sumY / vertexIndices.size();
	avgZ = sumZ / vertexIndices.size();
	scaleX = maxX - minX;
	scaleY = maxY - minY;
	scaleZ = maxZ - minZ;

	glm::vec3 temp;

	for (unsigned int i = 0; i < vertexIndices.size(); ++i)
	{
		temp = temp_vertices[vertexIndices[i] - 1];
		temp.x = temp.x - minX;
		temp.y = temp.y - minY;
		temp.z = temp.z - minZ;

		temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
		temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
		temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

		//m_outvertex.push_back(temp);
		m_outvertex.push_back(temp_vertices[vertexIndices[i] - 1]);
	}
	for (unsigned int i = 0; i < uvIndices.size(); ++i) {
		m_outuv.push_back(temp_uvs[uvIndices[i] - 1]);
	}
	for (unsigned int i = 0; i < normalIndices.size(); ++i) {
		m_outnormal.push_back(temp_normals[normalIndices[i] - 1]);
	}

	m_Tri_Num = m_outvertex.size();
}

GLuint s_program;

GLuint vao_line, vbo_line[2];
GLuint vao_cube, vbo_cube[3], ebo_cube;

void InitBuffer()
{
	glGenVertexArrays(1, &vao_line);
	glBindVertexArray(vao_line);
	glGenBuffers(2, vbo_line);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_line[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lines), lines, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_line[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lines_color), lines_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//----------------------------------------------

	glGenVertexArrays(1, &vao_cube);
	glBindVertexArray(vao_cube);
	glGenBuffers(3, vbo_cube);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube[0]);
	glBufferData(GL_ARRAY_BUFFER, m_outvertex.size() * sizeof(glm::vec3), &m_outvertex[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube[1]);
	glBufferData(GL_ARRAY_BUFFER, m_outnormal.size() * sizeof(glm::vec3), &m_outnormal[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube[2]);
	glBufferData(GL_ARRAY_BUFFER, m_outuv.size() * sizeof(glm::vec2), &m_outuv[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
}

GLenum polymode = GL_FILL;

GLfloat rot_x = 0.0f;
GLfloat rot_y = 0.0f;
GLfloat rot_z = 0.0f;

GLfloat move_x = 0.0f;
GLfloat move_y = 0.0f;
GLfloat move_z = 0.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ReadObj("ObjFiles/human.obj");

	InitBuffer();

	glEnable(GL_DEPTH_TEST);

	glUseProgram(s_program);

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
	Txr = glm::translate(Txr, glm::vec3(move_x, move_y, move_z)); //--- 역이동 행렬
	Rx = glm::rotate(Rx, glm::radians(rot_x), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	Ry = glm::rotate(Ry, glm::radians(rot_y), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	Rz = glm::rotate(Rz, glm::radians(rot_z), glm::vec3(0.0, 0.0, 1.0)); //--- z축에 대하여 회전 행렬
	Rt = Rx * Ry * Rz;
	TR = Txr * Rt * Tx;

	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));

	glBindVertexArray(vao_cube);
	glPolygonMode(GL_FRONT_AND_BACK, polymode);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_texture);
	glDrawArrays(GL_TRIANGLES, 0, m_Tri_Num);

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

	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
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

	glutPostRedisplay();
	glutTimerFunc(100, Timerfunc, 1);
}