#pragma once

#include "header.h"
#include "model.h"

class Plant : public Model
{
public:
	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void InitBuffer() = 0;
	virtual void InitTexture() = 0;
	virtual void Move_Update() = 0;
	virtual void Attack_Update() = 0;
	virtual void Render() = 0;
};