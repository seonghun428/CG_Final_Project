#pragma once

#include "plant.h"

class Bean : public Plant
{
private:
	Object* body;
	int x, y;
	GLfloat go_front = 0.0f;
	bool crash = true;
	int cnt = 0;

public:
	Bean(int mx, int my, string imgfile);
	~Bean();

	virtual void Move();
	virtual void Attack() {}
	virtual void Move_Update();
	virtual void Attack_Update() {}
	virtual void InitBuffer();

	virtual void set_state(int);

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();

	virtual void Get_Collide(Model* other, string group);

	virtual bool Get_Crash() { return crash; }
};