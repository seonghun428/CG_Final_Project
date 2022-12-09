#include "sunflower.h"

Sunflower::Sunflower()
{
	head = new Object("3DObjects/flower.obj", "Textures/flower.png");
	stem = new Object("3DObjects/stem.obj", "Textures/stem.png");
}

void Sunflower::InitBuffer()
{
	head->InitBuffer();
	stem->InitBuffer();
}

void Sunflower::InitTexture()
{
	head->InitTexture();
	stem->InitTexture();
}

void Sunflower::Render()
{
	head->Render();
	stem->Render();
}