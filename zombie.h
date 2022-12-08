#pragma once

#include "Cube.h"

class Zombie {
private:
	Cube* body;
	Cube* arm_left;
	Cube* arm_right;
	Cube* leg_left;
	Cube* leg_right;

	int line;

	bool leg_up = true; // øﬁπﬂ ±‚¡ÿ
	GLfloat leg_angle = 0.0f;
	GLfloat go_front = 0.0f;

public:
	Zombie(int line);
	~Zombie();

	void Move();

	void InitBuffer();
	void InitTexture();
	void Move_Update();
	void Render();
};