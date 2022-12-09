#include "cherry.h"

Cherry::Cherry()
{
	body = new Object("3DObjects/cherry.obj", "Textures/cherry.png");
}

void Cherry::InitBuffer()
{
	body->InitBuffer();
}

void Cherry::InitTexture()
{
	body->InitTexture();
}

void Cherry::Render()
{
	body->Render();
}