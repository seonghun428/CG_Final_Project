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
};