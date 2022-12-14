#pragma once

#include "model.h"

class Sun : public Model{
private:
	Object* body;

	GLfloat z_rotate = 0.0f;

public:
	Sun() {
		body = new Object("3DObjects/sun.obj", "Textures/sun.png");
		elements.push_back(body);
	}
	~Sun() { delete body; }

	virtual void Move() { z_rotate -= 0.1f; } //-0.1
	virtual void Move_Update() { body->Update_ZRotate_Matrix(z_rotate); }

	virtual GLfloat Get_z_rot() { return z_rotate; }
	virtual void Set_z_rot(GLfloat f) { z_rotate = f; }
};
