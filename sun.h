#pragma once

#include "header.h"
#include "object.h"
#include "model.h"

class Sun : public Model{
private:
	Object* body;

	GLfloat z_rotate = 0.0f;

public:
	Sun() { body = new Object("3D~~", "Textures/~~"); }
	~Sun() { delete body; }

	virtual void Move() { z_rotate += 0.5f; };
	virtual void Move_Update() { body->Update_ZRotate_Matrix(z_rotate); }
};
