#pragma once

#include "model.h"
#include "Shader.h"

class World
{
private:
	list<Model*> objects;
	// 충돌 그룹
	// map<string, tuple<Model*, Model*> collision_group;

public:
	list<Model*> all_object() { return objects; }
	void add_object(Model* o) { objects.push_back(o); }
	void remove_object(Model* o) { objects.remove(o); }
	void clear() { objects.clear(); }

	void setting(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, glm::vec3 lpos);
};