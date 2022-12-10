#pragma once

#include "model.h"
#include "object.h"

class Bean : public Model
{
private:
	Object* body;
	int x, y;
	GLfloat go_front = 0.0f;

public:
	Bean(int mx, int my);
	~Bean();

	virtual void Move();
	virtual void Attack() {}
	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Move_Update();
	virtual void Attack_Update() {}
	virtual void Render();
};