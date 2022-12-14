#pragma once

#include "header.h"
#include "object.h"

class Model
{
protected:
	vector<Object*> elements;

	int hp = 1;

	int bean_state = 0;

public:
	Model() {}
	virtual ~Model() {}

	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void Move_Update() = 0;
	virtual void Attack_Update() = 0;

	virtual void Get_Collide(Model* other, string group) {}
	virtual void set_state(int) {}
	virtual int get_state() { return bean_state; }

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();

	virtual glm::vec3 Get_Max() = 0;
	virtual glm::vec3 Get_Min() = 0;

	virtual bool Attacking() { return false; }
};