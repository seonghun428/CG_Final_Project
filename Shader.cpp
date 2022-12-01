#include "Shader.h"

GLuint Shader::ShaderID = NULL;

Shader::Shader()
{
	ShaderID = -1;
	vertexShader = -1;
	fragmentShader = -1;
}

void Shader::Make_VertexShader()
{
	GLchar* vertexSource = filetobuf("CG HW vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR : vertex shader 컴파일 실패\n" << errorLog << endl;
	}
}

void Shader::Make_FragmentShader()
{
	GLchar* fragmentSource = filetobuf("CG HW fragment.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR : vertex shader 컴파일 실패\n" << errorLog << endl;
	}
}

void Shader::InitShader()
{
	Make_VertexShader();
	Make_FragmentShader();

	ShaderID = glCreateProgram();

	glAttachShader(ShaderID, vertexShader);
	glAttachShader(ShaderID, fragmentShader);
	glLinkProgram(ShaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(ShaderID);
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fptr = fopen(file, "rb");

	if (!fptr)
		return NULL;

	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;

	return buf;
}