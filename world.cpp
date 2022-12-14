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

void World::clear()
{
	objects.clear();
	collision_group.clear();

	temp.clear();
	temp2.clear();
}

void World::remove_object(Model* o)
{
	objects.remove(o);
	remove_collision_object(o);
	// delete o;
}

void World::remove_collision_object(Model* o)
{
	temp.remove(o);
	temp2.remove(o);

	for (auto& pairs : collision_group)
	{
		for (auto& a : get<0>(pairs.second))
		{
			if (o == a) get<0>(pairs.second).remove(o);
			return;
		}
		for (auto& a : get<1>(pairs.second))
		{
			if (o == a) get<1>(pairs.second).remove(o);
			return;
		}
	}
}

void World::add_tuple(Model* o)
{
	temp.push_back(o);

	get<1>(group) = temp;
}

void World::add_tuple(list<Model*> l)
{
	get<0>(group) = l;
}

void World::add_tuple2(Model* o)
{ 
	temp2.push_back(o);

	if (get<0>(group2).empty())
	{
		get<0>(group2) = temp2;
		temp2.clear();
	}
	else
		get<1>(group2) = temp2;
}

void World::add_collision_group(string group, Model* a, Model* b)
{
	list<Model*> temp;
	temp.push_back(a);
	list<Model*> temp2;
	temp2.push_back(b);

	collision_group.insert(make_pair(group, make_tuple(temp, temp2)));
}

void World::add_collision_group(string group, Model* a, list<Model*> b)
{
	list<Model*> temp;
	temp.push_back(a);

	collision_group.insert(make_pair(group, make_tuple(temp, b)));
}

void World::add_collision_group(string group, tuple<list<Model*>,list<Model*>> a)
{
	if (collision_group.find(group) != collision_group.end())
		collision_group.erase(group);
	collision_group.insert(make_pair(group, a));
}

map<string, tuple<list<Model*>, list<Model*>>> World::all_collision_group()
{
	map<string, tuple<list<Model*>, list<Model*>>> temp;
	temp.insert(collision_group.begin(), collision_group.end());
	return temp;
}