#pragma once

#include "header.h"
#include "object.h"

class Model
{
protected:
	vector<Object*> elements;

public:
	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void InitBuffer() = 0;
	virtual void InitTexture() = 0;
	virtual void Move_Update() = 0;
	virtual void Attack_Update() = 0;
	virtual void Render() = 0;

	virtual glm::vec3 Get_Max() = 0;
	virtual glm::vec3 Get_Min() = 0;
};