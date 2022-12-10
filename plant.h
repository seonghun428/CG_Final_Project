#pragma once

#include "header.h"
#include "model.h"

class Plant : public Model
{
public:
	virtual void InitBuffer() = 0;
	virtual void InitTexture() = 0;
	virtual void Render() = 0;
};