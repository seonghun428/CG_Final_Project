#pragma once

#include "object.h"
#include "model.h"

class Plane : public Model
{
private:
	Object* body;

public:
	Plane() { body = new Object("3DObjects/plane.obj", "Textures/plane2.png");
			  elements.push_back(body); }

	~Plane() { delete body; }

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max() { return body->Get_Max_O(); }
	virtual glm::vec3 Get_Min() { return body->Get_Min_O(); }
	virtual void Get_Collide(Model* other, string group) {}
};