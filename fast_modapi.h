#pragma once

#include "plant.h"
#include "object.h"

class F_Modapi : public Plant
{
private:
	Object* hair;
	Object* head;
	Object* stem;

public:
	F_Modapi();

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();
};