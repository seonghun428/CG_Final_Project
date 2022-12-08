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
	Peanut(const string objfile, const string imgfile);

	virtual void InitBuffer();
	virtual void InitTexture();
	virtual void Render();
};