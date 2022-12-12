#pragma once

#include "model.h"

class Wall : public Model
{
private:
	Object* body;

public:
	Wall(int a) {
		if (a == 0) body = new Object("3DObjects/back_wall.obj", "Textures/gold.png");
		else if (a == 1) body = new Object("3DObjects/front_wall.obj", "Textures/gold.png");
		elements.push_back(body);
	}
	~Wall() { delete body; }

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max() { return body->Get_Max_O(); }
	virtual glm::vec3 Get_Min() { return body->Get_Min_O(); }
	virtual void Get_Collide(Model* other, string group) {}
};