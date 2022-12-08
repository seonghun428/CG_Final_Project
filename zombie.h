#pragma once

#include "object.h"

class Zombie {
private:
	Object* body;
	Object* arm_left;
	Object* arm_right;
	Object* leg_left;
	Object* leg_right;

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