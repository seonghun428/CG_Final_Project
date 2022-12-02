#pragma once

#include "Cube.h"

class Zombie {
private:
	Cube body{ "3DObjects/zombie_body.obj" };
	Cube arm_left{ "3DObjects/zombie_arm_left.obj" };
	Cube arm_right{ "3DObjects/zombie_arm_right.obj" };
	Cube leg_left{ "3DObjects/zombie_leg_left.obj" };
	Cube leg_right{ "3DObjects/zombie_leg_right.obj" };

	bool leg_up = true; // øﬁπﬂ ±‚¡ÿ
	GLfloat leg_angle = 0.0f;

public:
	void Move();

	void InitBuffer();
	void Update();
	void Render();
};