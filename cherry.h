#pragma once

#include "plant.h"
#include "object.h"

class Cherry : public Plant
{
private:
	Object* body;

public:
	Cherry(int x, int y);
	~Cherry();

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();
};