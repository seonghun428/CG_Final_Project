#pragma once

#include "plant.h"
#include "object.h"

class P_Modapi : public Plant
{
private:
	Object* hair;
	Object* head;
	Object* stem;

public:
	P_Modapi();

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();
};