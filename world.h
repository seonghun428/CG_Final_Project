#pragma once

#include "model.h"
#include "Shader.h"

class World
{
private:
	list<Model*> objects;
	map<string, tuple<list<Model*>, list<Model*>>> collision_group;
	tuple<list<Model*>, list<Model*>> group;
	tuple<list<Model*>, list<Model*>> group2;
	list<Model*> temp;
	list<Model*> temp2;

public:
	list<Model*> all_object() { return objects; }
	void add_object(Model* o) { objects.push_back(o); }
	void remove_object(Model* o);
	void clear();

	void add_collision_group(string group, Model* a, Model* b);
	void add_collision_group(string group, tuple<list<Model*>, list<Model*>> a);
	void remove_collision_object(Model* o);

	void add_tuple(Model* o);
	void add_tuple2(Model* o);

	tuple<list<Model*>, list<Model*>> get_group() { return group; }
	tuple<list<Model*>, list<Model*>> get_group2() { return group2; }

	map < string, tuple<list<Model*>, list<Model*>>> all_collision_group();

	void setting(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, glm::vec3 lpos);
};