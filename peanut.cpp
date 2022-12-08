#include "peanut.h"

Peanut::Peanut() {}

Peanut::Peanut(const string objfile, const string imgfile)
{
	body = new Object(objfile, imgfile);
}

void Peanut::InitBuffer()
{
	body->InitBuffer();

	body->Update_YRotate_Matrix(90.0f);
}

void Peanut::InitTexture()
{
	body->InitTexture();
}

void Peanut::Render()
{
	body->Render();
}