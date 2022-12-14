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

	GLfloat minX = 10000.0f, minY = 10000.0f, minZ = 10000.0f;
	GLfloat maxX = -10000.0f, maxY = -10000.0f, maxZ = -10000.0f;

	glm::vec3 vertex;
	glm::vec2 uv;
	glm::vec3 normal;

	vector<glm::vec3> temp_vertices;
	vector<glm::vec3> temp_normals;
	vector<glm::vec2> temp_uvs;

	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

	vector<unsigned int> vertexIndices, normalIndices, uvIndices;

	glm::mat4 Tm = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 Sc = glm::mat4(1.0f);

	glm::mat4 Sm = glm::mat4(1.0f);

	glm::vec3 Max = glm::vec3(0.0f);
	glm::vec3 Min = glm::vec3(0.0f);

public:
	Object(const string objFile, const string imgfile);

	void InitBuffer();
	void InitTexture();

	void Reset_Matrix();

	void Update_Translate_Matrix(glm::vec3);
	void Update_XRotate_Matrix(GLfloat);
	void Update_YRotate_Matrix(GLfloat);
	void Update_ZRotate_Matrix(GLfloat);
	void Update_Scale_Matrix(glm::vec3);

	void Render();

	glm::vec3 Get_Max_O() { return Max; }
	glm::vec3 Get_Min_O() { return Min; }
	
	void ReadObj(const string objFile);
};
