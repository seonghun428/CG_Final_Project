#pragma once

#include "header.h"
#include "plant.h"
#include "object.h"

class Peanut : public Plant
{
private:
	Object* body;

public:
	Peanut();

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();
};