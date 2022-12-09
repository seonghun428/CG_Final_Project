#pragma once

#include "plant.h"
#include "object.h"

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
};