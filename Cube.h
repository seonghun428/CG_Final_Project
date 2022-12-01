#pragma once

#include "header.h"

class Cube
{
private:
	GLuint vao;
	GLuint vbo[2];
	GLuint ebo;

	glm::vec3* Position;
	glm::vec3* Color;

	int Index[6][6] = {
		// 아래
		{ 0, 1, 4, 1, 4, 5 },

		// 위
		{ 2, 3, 6, 3, 6, 7 },

		// 왼쪽
		{ 0, 1, 2, 1, 2, 3 },

		// 오른쪽
		{ 4, 5, 6, 5, 6, 7 },

		// 앞
		{ 0, 2, 6, 0, 4, 6 },

		// 뒤
		{ 1, 3, 7, 1, 5, 7 }
	};

	int vertexNum;

	bool Y_Move = true;

	glm::mat4 Sm = glm::mat4(1.0f);

public:
	Cube();
	Cube(int xnum, int ynum, glm::vec3 color);

	void InitBuffer();
	void InitColor();

	void Set_Position(int xnum, int ynum, int count);

	void Move_Y_Position(GLfloat mult);
	void Reset_Y_Position();

	void Move(int xnum, int ynum, int direction);

	glm::vec3 get_Position();

	void Update_Synthetic_Matrix();

	void Render();
};

void ReadObj(const char* obj, glm::vec3** shape, int* vnum, GLfloat sizex, GLfloat sizey, GLfloat sizez);