#pragma once

#include "model.h"

class Plant : public Model
{
protected:
	int x, y;
	int cost = 0;

public:
	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void Move_Update() = 0;
	virtual void Attack_Update() = 0;

	virtual void InitBuffer();

	virtual glm::vec3 Get_Max() = 0;
	virtual glm::vec3 Get_Min() = 0;
	virtual void Get_Collide(Model* other, string group);

	virtual int Get_Cost() { return cost; }
};