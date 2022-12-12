#pragma once

#include "model.h"

class Mower : public Model
{
private:
	Object* body;

	int line;

public:
	Mower();
	Mower(int line);
	~Mower();

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}
	virtual void InitBuffer();

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();
};