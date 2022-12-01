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
	GLchar* vertexSource = filetobuf("vertex.glsl");
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
	GLchar* fragmentSource = filetobuf("fragment.glsl");
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

char* filetobuf(const string file)
{
	string code;
	ifstream fin(file, ios::in);
	if (fin.is_open())
	{
		string Line = "";
		while (getline(fin, Line))
			code += "\n" + Line;
		fin.close();
	}
	else
		return 0;
	char* buf = new char[code.length() + 1];
	strcpy(buf, code.c_str());
	return buf;
}