#pragma once

#include "model.h"

class Zombie : public Model
{
protected:
	Object* body;
	Object* arm_left;
	Object* arm_right;
	Object* leg_left;
	Object* leg_right;

	int line;
	int num;

	bool leg_up = true; // øﬁπﬂ ±‚¡ÿ
	bool arm_up = true;

	bool attack = false;
	bool slowed = false;

	GLfloat leg_angle = 0.0f;
	GLfloat arm_angle = 0.0f;
	GLfloat go_front = 0.0f;

public:
	Zombie();
	Zombie(int line, int num);
	~Zombie();
	
	virtual void Move();
	virtual void Attack();
	virtual void Move_Update();
	virtual void Attack_Update();
	virtual void InitBuffer();

	virtual glm::vec3 Get_Max();
	virtual glm::vec3 Get_Min();
	virtual void Get_Collide(Model* other, string group);

	virtual bool Attacking();
};