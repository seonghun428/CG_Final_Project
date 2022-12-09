#pragma once

#include "plant.h"
#include "object.h"

class S_Modapi : public Plant
{
private:
	Object* hair;
	Object* head;
	Object* stem;

public:
	S_Modapi();

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();
};