#pragma once

#include "zombie.h"

class IronZombie : public Zombie
{
private:
	Object* head;
	Object* body;
	Object* arm_left;
	Object* arm_right;
	Object* leg_left;
	Object* leg_right;

	int line;

	bool leg_up = true; // øﬁπﬂ ±‚¡ÿ
	bool arm_up = true;
	GLfloat leg_angle = 0.0f;
	GLfloat arm_angle = 0.0f;
	GLfloat go_front = 0.0f;

public:
	IronZombie(int line);
	~IronZombie();

	virtual void Move();
	virtual void Attack();
	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Move_Update();
	virtual void Attack_Update();
	virtual void Render();
};