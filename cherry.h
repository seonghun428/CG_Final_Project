#pragma once

#include "plant.h"
#include "object.h"

class Cherry : public Plant
{
private:
	Object* body;

public:
	Cherry();

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();

	virtual void Move() {}
	virtual void Attack() {}
	virtual void Move_Update() {}
	virtual void Attack_Update() {}
};