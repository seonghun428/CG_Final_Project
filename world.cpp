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
	objects.remove(o);

	for (auto& a : collision_group)
	{
		for (auto& b : get<0>(a.second))
		{
			if (o == b)
			{
				collision_group.erase(a.first);
				return;
			}
		}

		for (auto& b : get<1>(a.second))
		{
			if (o == b)
			{
				collision_group.erase(a.first);
				return;
			}
		}
	}
}

void World::add_tuple(Model* o)
{
	temp.push_back(o);

	if (get<0>(group).empty())
	{
		get<0>(group) = temp;
		temp.clear();
	}
	else
		get<1>(group) = temp;
}

void World::add_tuple(list<Model*> o)
{
	if (get<0>(group).empty())
		get<0>(group) = o;
	else
		get<1>(group) = o;
}

void World::add_collision_group(string group, Model* a, Model* b)
{
	list<Model*> temp;
	temp.push_back(a);
	list<Model*> temp2;
	temp2.push_back(b);

	collision_group.insert(make_pair(group, make_tuple(temp, temp2)));
}

void World::add_collision_group(string group, tuple<list<Model*>,list<Model*>> a)
{
	if (collision_group.find(group) != collision_group.end())
		collision_group.erase(group);
	collision_group.insert(make_pair(group, a));
}

map<string, tuple<list<Model*>, list<Model*>>> World::all_collision_group()
{
	return collision_group;
}