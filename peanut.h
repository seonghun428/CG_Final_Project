#pragma once

#include "header.h"
#include "plant.h"
#include "object.h"

class Peanut : public Plant
{
private:
	Object* body;

public:
	Peanut();

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();
};