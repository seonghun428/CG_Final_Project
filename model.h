#pragma once

#include "header.h"
#include "object.h"

class Model
{
protected:
	vector<Object*> elements;

	int hp = 5;

	int bean_state = 0;

public:
	Model() {}
	virtual ~Model() {}

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual void Get_Collide(Model* other, string group) {}
	virtual void set_state(int) {}
	virtual int get_state() { return bean_state; }

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();

	virtual glm::vec3 Get_Max() { return glm::vec3(0.0f); }
	virtual glm::vec3 Get_Min() { return glm::vec3(0.0f); }

	virtual int Get_Hp() { return hp; }

	virtual bool Attacking() { return false; }
	virtual bool Get_Crash() { return false; }

	virtual GLfloat Get_z_rot() { return 0; }
	virtual void Set_z_rot(GLfloat) {}

	virtual int Get_Cost() { return 0; }
};