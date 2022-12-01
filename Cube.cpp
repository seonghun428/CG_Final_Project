#include "Cube.h"
#include "Shader.h"

Cube::Cube()
{
	ReadObj("Cube.obj", &Position, &vertexNum, 5, 0.2, 5);

	Color = new glm::vec3[vertexNum];

	for (unsigned int i = 0; i < vertexNum; ++i) {
		Color[i] = glm::vec3(0.28f, 0.54f, 0.36f);
	}
}

Cube::Cube(int xnum, int ynum, glm::vec3 color)
{
	ReadObj("Cube.obj", &Position, &vertexNum, 4.0 / xnum, 0.3, 4.0 / ynum);

	/*Color = new glm::vec3[vertexNum];



	for (unsigned int i = 0; i < vertexNum; ++i) {
		Color[i] = color;
	}*/

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0f, 1.0f);

	Color = new glm::vec3[vertexNum];

	for (unsigned int i = 0; i < vertexNum; ++i) {
		Color[i] = glm::vec3(dis(rd), dis(rd), dis(rd));
	}
}

void Cube::Move(int xnum, int ynum, int direction)
{
	switch (direction) {
	case 0:
		// 상
		for (unsigned int j = 0; j < 8; ++j)
			Position[j].z -= (2.0 / ynum);

		break;

	case 1:
		// 하
		for (unsigned int j = 0; j < 8; ++j)
			Position[j].z += (2.0 / ynum);

		break;

	case 2:
		// 좌
		for (unsigned int j = 0; j < 8; ++j)
			Position[j].x -= (2.0 / xnum);

		break;

	case 3:
		// 우
		for (unsigned int j = 0; j < 8; ++j)
			Position[j].x += (2.0 / xnum);

		break;
	}
}
glm::vec3 Cube::get_Position()
{
	return glm::vec3((Position[0].x + Position[7].x) / 2.0, 0.0, (Position[0].z + Position[1].z) / 2.0);
}

void Cube::Set_Position(int xnum, int ynum, int count)
{
	/*for (unsigned int i = 0; i < xnum; ++i) {
		Position->x = 
	}*/
	for (unsigned int j = 0; j < 8; ++j) {
		if (j % 2 == 0)
			Position[j].x = -1.0 + (count % xnum) * (2.0 / xnum);

		else
			Position[j].x = -1.0 + ((count % xnum) + 1) * (2.0 / xnum);
		
		if (j < 4)
			Position[j].z = -1.0 + (count / ynum) * (2.0 / xnum);

		else
			Position[j].z = -1.0 + ((count / ynum) + 1) * (2.0 / xnum);

		Position[j].y += 0.005f;
	}
}

void Cube::Move_Y_Position(GLfloat mult)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.01f, 0.1f);

	GLfloat y_move = dis(rd) * mult;

	if (Position[2].y >= 1.5f) {
		Y_Move = false;
	}

	if (Position[2].y <= 0.2f) {
		Y_Move = true;
	}

	if (Y_Move) {
		Position[2].y += y_move;
		Position[3].y += y_move;
		Position[6].y += y_move;
		Position[7].y += y_move;
	}

	else {
		Position[2].y -= y_move;
		Position[3].y -= y_move;
		Position[6].y -= y_move;
		Position[7].y -= y_move;
	}
}

void Cube::Reset_Y_Position()
{
	Position[2].y = 0.2;
	Position[3].y = 0.2;
	Position[6].y = 0.2;
	Position[7].y = 0.2;
}

void Cube::InitColor()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0f, 1.0f);

	for (unsigned int i = 0; i < vertexNum; ++i) {
		Color[i] = glm::vec3(dis(rd), dis(rd), dis(rd));
	}
}

void Cube::InitBuffer()
{
	// vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// vbo
	glGenBuffers(2, vbo);

	// Position
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, _msize(Position), Position, GL_STATIC_DRAW);

	// Index
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index), Index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	// Color
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, _msize(Color), Color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

void Cube::Update_Synthetic_Matrix()
{
	unsigned int modelLocation = glGetUniformLocation(Shader::Get_ShaderID(), "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Sm));
}

void Cube::Render()
{
	glUseProgram(Shader::Get_ShaderID());
	glBindVertexArray(vao);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void ReadObj(const char* obj, glm::vec3** shape, int* vnum, GLfloat sizex, GLfloat sizey, GLfloat sizez)
{
	FILE* objFile = fopen(obj, "r");
	glm::vec3* Shape;

	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기
	char count[100];
	int vertexNum = 0;
	int faceNum = 0;

	if (objFile == NULL) {
		return;
	}

	while (!feof(objFile)) {
		fscanf(objFile, "%s", count);

		if (count[0] == 'v' && count[1] == '\0')
			vertexNum += 1;

		else if (count[0] == 'f' && count[1] == '\0')
			faceNum += 1;

		memset(count, '\0', sizeof(count)); // 배열 초기화
	}

	fseek(objFile, 0, SEEK_SET);

	//--- 2. 메모리 할당
	glm::vec4* vertex;
	glm::vec4* face;

	char bind[100];
	int vertIndex = 0;
	int faceIndex = 0;

	vertex = new glm::vec4[vertexNum];
	face = new glm::vec4[faceNum];

	//--- 3. 할당된 메모리에 각 버텍스, 페이스 정보 입력
	while (!feof(objFile)) {
		fscanf(objFile, "%s", bind);

		if (bind[0] == 'v' && bind[1] == '\0') {
			fscanf(objFile, "%f %f %f",
				&vertex[vertIndex].x, &vertex[vertIndex].y,
				&vertex[vertIndex].z);
			vertIndex++;
		}

		else if (bind[0] == 'f' && bind[1] == '\0') {
			fscanf(objFile, "%f %f %f",
				&face[faceIndex].x, &face[faceIndex].y, &face[faceIndex].z);
			faceIndex++;
		}
	}

	fclose(objFile);

	Shape = new glm::vec3[vertexNum];

	for (int i = 0; i < vertexNum; ++i) {
		Shape[i].x = vertex[i].x * sizex;
		Shape[i].y = vertex[i].y * sizey;
		Shape[i].z = vertex[i].z * sizez;
	}

	*shape = Shape;
	*vnum = vertexNum;

	delete[] vertex, face, Shape;
}