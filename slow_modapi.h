#pragma once

#include "plant.h"

class S_Modapi : public Plant
{
private:
	Object* hair;
	Object* head;
	Object* stem;

public:
	S_Modapi(int x, int y);
	~S_Modapi();

	virtual void Attack();
	virtual void Move() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();
};