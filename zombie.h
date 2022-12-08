#pragma once

#include "object.h"

class Zombie {
public:
	virtual void Move() = 0;

	virtual void InitBuffer() = 0;
	virtual void InitTexture() = 0;
	virtual void Move_Update() = 0;
	virtual void Render() = 0;
};