#pragma once

#include "plant.h"
#include "object.h"

class Sunflower : public Plant
{
private:
	Object* head;
	Object* stem;

public:
	Sunflower();

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();
};