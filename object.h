#pragma once

#include "header.h"

class Object
{
private:
	GLuint vao;
	GLuint vbo[3];

	GLint m_Tri_Num = 0;

	unsigned int m_texture;

	int widthImage, heightImage, numberOfChannel;
	unsigned char* data;

	vector<glm::vec3> m_outvertex;
	vector<glm::vec3> m_outnormal;
	vector<glm::vec2> m_outuv;

	glm::mat4 Tm = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);

	glm::mat4 Sm = glm::mat4(1.0f);

	glm::vec3 Max = glm::vec3(0.0f);
	glm::vec3 Min = glm::vec3(0.0f);

public:
	Object();
	Object(const string objFile, const string imgfile);
	~Object();

	void InitBuffer();
	void InitTexture();

	void Reset_Matrix();

	void Update_Translate_Matrix(glm::vec3);
	void Update_XRotate_Matrix(GLfloat);
	void Update_YRotate_Matrix(GLfloat);
	void Update_ZRotate_Matrix(GLfloat);

	void Update_Synthetic_Matrix();

	void Render();

	glm::vec3 Get_Max_O() { return Max; }
	glm::vec3 Get_Min_O() { return Min; }
	
	void ReadObj(const string objFile);
};
