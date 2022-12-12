#pragma once

#include "plant.h"
#include "object.h"

class Sunflower : public Plant
{
private:
	Object* head;
	Object* stem;

public:
	Sunflower();
	~Sunflower();

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();
};