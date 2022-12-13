#pragma once

#include "model.h"

class Wall : public Model
{
private:
	Object* body;

public:
	Wall(int a);
	~Wall();

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();
	virtual void Get_Collide(Model* other, string group);
};