#pragma once

#include "plant.h"
#include "object.h"
#include "scene.h"

extern Scene scene;

class Modapi : public Plant
{
private:
	Object* head;
	Object* stem;

public:
	Modapi();

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();

	virtual void Move() {}
	virtual void Attack();
	virtual void Move_Update() {}
	virtual void Attack_Update() {}
};