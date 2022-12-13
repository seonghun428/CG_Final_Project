#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include "object.h"
#include "Shader.h"

Object::Object(const string objFile, const string imgfile)
{
	ReadObj(objFile);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(imgfile.c_str(), &widthImage, &heightImage, &numberOfChannel, 0);
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
	ifstream fin{ objFile };
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
				fin >> vertex.x >> vertex.y >> vertex.z;
				if (vertex.x < minX) minX = vertex.x;
				if (vertex.y < minY) minY = vertex.y;
				if (vertex.z < minZ) minZ = vertex.z;
				if (vertex.x > maxX) maxX = vertex.x;
				if (vertex.y > maxY) maxY = vertex.y;
				if (vertex.z > maxZ) maxZ = vertex.z;

				temp_vertices.push_back(vertex);
			}

			else if (line[0] == 'v' && line[1] == 't') {
				fin >> uv.x >> uv.y;
				temp_uvs.push_back(uv);
			}

			else if (line[0] == 'v' && line[1] == 'n') {
				fin >> normal.x >> normal.y >> normal.z;
				temp_normals.push_back(normal);
			}

			else if (line[0] == 'f' && line[1] == '\0') {
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

	for (unsigned int i = 0; i < vertexIndices.size(); ++i)
	{
		m_outvertex.push_back(temp_vertices[vertexIndices[i] - 1]);
	}
	for (unsigned int i = 0; i < uvIndices.size(); ++i) {
		m_outuv.push_back(temp_uvs[uvIndices[i] - 1]);
	}
	for (unsigned int i = 0; i < normalIndices.size(); ++i) {
		m_outnormal.push_back(temp_normals[normalIndices[i] - 1]);
	}

	temp_vertices.clear();
	temp_uvs.clear();
	temp_normals.clear();
	vertexIndices.clear();
	uvIndices.clear();
	normalIndices.clear();

	m_Tri_Num = m_outvertex.size();

	Max = glm::vec3(maxX, maxY, maxZ);
	Min = glm::vec3(minX, minY, minZ);
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