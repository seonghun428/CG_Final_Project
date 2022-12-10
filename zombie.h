#pragma once

#include "object.h"
#include "model.h"

class Zombie : public Model
{
public:
	virtual void Move() = 0;

	virtual void InitBuffer() = 0;
	virtual void InitTexture() = 0;
	virtual void Move_Update() = 0;
	virtual void Render() = 0;
};