#pragma once

#include "header.h"

class Cube
{
private:
	GLuint vao;
	GLuint vbo[3];

	GLint m_Tri_Num;

	vector<glm::vec3> m_outvertex;
	vector<glm::vec3> m_outnormal;
	vector<glm::vec2> m_outuv;

	bool Y_Move = true;

	glm::mat4 Sm = glm::mat4(1.0f);

public:
	Cube();
	Cube(const string objFile);

	void InitBuffer();
	void InitColor();

	void Set_Position(int xnum, int ynum, int count);

	void Move_Y_Position(GLfloat mult);
	void Reset_Y_Position();

	void Move(int xnum, int ynum, int direction);

	glm::vec3 get_Position();

	void Update_Synthetic_Matrix();

	void Render();
	
	void ReadObj(const string objFile);
};
