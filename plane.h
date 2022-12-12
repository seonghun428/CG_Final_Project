#pragma once

#include "object.h"
#include "model.h"

class Plane : public Model
{
private:
	Object* body;

public:
	Plane() { body = new Object("3DObjects/plane.obj", "Textures/plane.png");
			  elements.push_back(body); }

	~Plane() { delete body; }

	virtual void Move() {}
	virtual void Attack() {}
	virtual void InitBuffer() { body->InitBuffer(); }
	virtual void InitTexture() { body->InitTexture(); }
	virtual void Move_Update() {}
	virtual void Attack_Update() {}
	virtual void Render() { body->Render(); }

	virtual glm::vec3 Get_Max() { return body->Get_Max_O(); }
	virtual glm::vec3 Get_Min() { return body->Get_Min_O(); }
};