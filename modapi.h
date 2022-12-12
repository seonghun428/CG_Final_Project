#pragma once

#include "model.h"

class Modapi :public Model {
protected:
	Object* head;
	Object* stem;

public:
	Modapi();
	~Modapi();

	virtual void Attack();
	virtual void Move() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();
};