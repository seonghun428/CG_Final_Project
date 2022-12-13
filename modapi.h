#pragma once

#include "plant.h"

class Modapi :public Plant {
private:
	Object* head;
	Object* stem;

public:
	Modapi(int x, int y);
	~Modapi();

	virtual void Attack();
	virtual void Move() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();
};