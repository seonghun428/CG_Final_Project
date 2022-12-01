#pragma once

#include "header.h"

class Shader
{
private:
	static GLuint ShaderID;

	GLuint vertexShader;
	GLuint fragmentShader;

public:
	Shader();

	void Make_VertexShader();
	void Make_FragmentShader();
	void InitShader();

	static GLuint Get_ShaderID()
	{
		if (ShaderID != NULL) {
			return ShaderID;
		}

		return 0;
	}
};

char* filetobuf(const string file);
