#include "world.h"

void World::setting(glm::vec3 cpos, glm::vec3 dir, glm::vec3 up, glm::vec3 lpos)
{
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cpos, dir, up);
	unsigned int viewLocation = glGetUniformLocation(Shader::Get_ShaderID(), "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int lightPosLocation = glGetUniformLocation(Shader::Get_ShaderID(), "lightPos");
	glUniform3f(lightPosLocation, lpos.x, lpos.y, lpos.z);
	unsigned int lightColorLocation = glGetUniformLocation(Shader::Get_ShaderID(), "lightColor");
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
	unsigned int objColorLocation = glGetUniformLocation(Shader::Get_ShaderID(), "objectColor");
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	unsigned int viewPosLocation = glGetUniformLocation(Shader::Get_ShaderID(), "viewPos");
	glUniform3f(viewPosLocation, cpos.x, cpos.y, cpos.z);
}