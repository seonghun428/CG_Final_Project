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

void World::remove_object(Model* o)
{
	for (auto& a : collision_group)
	{
		if (o == get<0>(a.second) || o == get<1>(a.second))
		{
			collision_group.erase(a.first);
		}
	}

	objects.remove(o);
}

void World::add_tuple(Model* o)
{
	if (get<0>(group) == nullptr)
		get<0>(group) = o;
	else
		get<1>(group) = o;
}

void World::add_collision_group(string group, Model* a, Model* b)
{
	collision_group.insert(make_pair(group, make_tuple(a, b)));
}

void World::add_collision_group(string group, tuple<Model*,Model*> a)
{
	collision_group.insert(make_pair(group, a));
}

map<string, tuple<Model*, Model*>> World::all_collision_group()
{
	return collision_group;
}