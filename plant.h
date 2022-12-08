#pragma once

#include "header.h"

class Plant
{
public:
	virtual void InitBuffer() = 0;
	virtual void InitTexture() = 0;
	virtual void Render() = 0;
};