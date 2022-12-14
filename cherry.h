#pragma once

#include "plant.h"
#include "object.h"

class Cherry : public Plant
{
private:
	Object* body;
	int cnt = 0;
	bool crash = false;
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);

public:
	Cherry(int x, int y);
	~Cherry();

	virtual void Move();
	virtual void Attack() {}
	virtual void Move_Update();
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();
	virtual bool Get_Crash() { return crash; }
};