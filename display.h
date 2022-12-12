#pragma once

#include "model.h"

class Display : public Model
{
private:
	Object* body;

public:
	Display(string imgfile) {
		body = new Object("3DObjects/cube.obj", imgfile);
		elements.push_back(body);
	}
	~Display() { delete body; }

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}

	virtual glm::vec3 Get_Max() { return body->Get_Max_O(); }
	virtual glm::vec3 Get_Min() { return body->Get_Min_O(); }
	virtual void Get_Collide(Model* other, string group) {}
};