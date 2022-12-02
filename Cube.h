#pragma once

#include "header.h"

class Cube
{
private:
	GLuint vao;
	GLuint vbo[3];

	GLint m_Tri_Num = 0;

	vector<glm::vec3> m_outvertex;
	vector<glm::vec3> m_outnormal;
	vector<glm::vec2> m_outuv;

	bool Y_Move = true;

	glm::mat4 Tm = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);

	glm::mat4 Sm = glm::mat4(1.0f);

public:
	Cube();
	Cube(const string objFile);

	void InitBuffer();

	void Reset_Matrix();

	void Update_Translate_Matrix(glm::vec3);
	void Update_XRotate_Matrix(GLfloat);
	void Update_YRotate_Matrix(GLfloat);
	void Update_ZRotate_Matrix(GLfloat);

	void Update_Synthetic_Matrix();

	void Render();
	
	void ReadObj(const string objFile);
};
