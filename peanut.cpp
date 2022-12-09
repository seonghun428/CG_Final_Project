#include "peanut.h"

Peanut::Peanut()
{
	body = new Object("3DObjects/peanut.obj", "Textures/peanut.png");
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