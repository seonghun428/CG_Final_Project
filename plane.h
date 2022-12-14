#pragma once

#include "model.h"

class Plane : public Model
{
private:
	Object* body;
	Object* ground;

public:
	Plane() {
		body = new Object("3DObjects/plane.obj", "Textures/plane2.png");
		ground = new Object("3DObjects/ground.obj", "Textures/ground.png");
		elements.push_back(body);
		elements.push_back(ground);
	}

	~Plane() {
		delete body;
		delete ground;
	}

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max() { return body->Get_Max_O(); }
	virtual glm::vec3 Get_Min() { return body->Get_Min_O(); }
	virtual void Get_Collide(Model* other, string group) {}
};