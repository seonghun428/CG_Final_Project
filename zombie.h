#pragma once

#include "Cube.h"

class Zombie {
private:
	Cube* body;
	Cube* arm_left;
	Cube* arm_right;
	Cube* leg_left;
	Cube* leg_right;

	bool leg_up = true; // øﬁπﬂ ±‚¡ÿ
	GLfloat leg_angle = 0.0f;

public:
	Zombie();
	~Zombie();

	void Move();

	void InitBuffer();
	void Move_Update();
	void Render();
};