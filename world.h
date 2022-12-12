#pragma once

#include "model.h"
#include "Shader.h"

class World
{
private:
	list<Model*> objects;
	map<string, tuple<list<Model*>, list<Model*>>> collision_group;
	tuple<list<Model*>, list<Model*>> group;
	list<Model*> temp;

public:
	list<Model*> all_object() { return objects; }
	void add_object(Model* o) { objects.push_back(o); }
	void remove_object(Model* o);
	void clear() { objects.clear(); collision_group.clear(); }

	void add_collision_group(string group, Model* a, Model* b);
	void add_collision_group(string group, tuple<list<Model*>, list<Model*>> a);

	void add_tuple(Model* o);
	void add_tuple(list<Model*> o);

	tuple<list<Model*>, list<Model*>> get_group() { return group; }

	map < string, tuple<list<Model*>, list<Model*>>> all_collision_group();

	void setting(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, glm::vec3 lpos);
};