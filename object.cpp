#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include "object.h"
#include "Shader.h"

Object::Object() {}

Object::Object(const string objFile, const string imgfile)
{
	ReadObj(objFile);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(imgfile.c_str(), &widthImage, &heightImage, &numberOfChannel, 0);
}

Object::~Object()
{
	
}

void Object::InitBuffer()
{
	// vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// vbo
	glGenBuffers(3, vbo);

	// Position
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, m_outvertex.size() * sizeof(glm::vec3), &m_outvertex[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, m_outnormal.size() * sizeof(glm::vec3), &m_outnormal[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, m_outuv.size() * sizeof(glm::vec2), &m_outuv[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);

	Sm = glm::mat4(1.0f);
}

void Object::InitTexture()
{
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Object::Update_Synthetic_Matrix()
{
	
}

void Object::Render()
{
	unsigned int modelLocation = glGetUniformLocation(Shader::Get_ShaderID(), "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Sm));

	glUseProgram(Shader::Get_ShaderID());
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glDrawArrays(GL_TRIANGLES, 0, m_Tri_Num);
}

void Object::ReadObj(const string objFile)
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

void Object::Update_Translate_Matrix(glm::vec3 move)
{
	Tm = glm::mat4(1.0f);
	Tm = glm::translate(Tm, move);
	Sm *= Tm;
}

void Object::Update_XRotate_Matrix(GLfloat x_angle)
{
	Rx = glm::mat4(1.0f);
	Rx = glm::rotate(Rx, glm::radians(x_angle), glm::vec3(1.0, 0.0, 0.0));
	Sm *= Rx;
}

void Object::Update_YRotate_Matrix(GLfloat y_angle)
{
	Ry = glm::mat4(1.0f);
	Ry = glm::rotate(Ry, glm::radians(y_angle), glm::vec3(0.0, 1.0, 0.0));
	Sm *= Ry;
}

void Object::Update_ZRotate_Matrix(GLfloat z_angle)
{
	Rz = glm::mat4(1.0f);
	Rz = glm::rotate(Rz, glm::radians(z_angle), glm::vec3(0.0, 0.0, 1.0));
	Sm *= Rz;
}

void Object::Reset_Matrix()
{
	Sm = glm::mat4(1.0f);
}