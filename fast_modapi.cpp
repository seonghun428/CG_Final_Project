#include "fast_modapi.h"

F_Modapi::F_Modapi()
{
	hair = new Object("3DObjects/leaf_2.obj", "Textures/leaf.png");
	head = new Object("3DObjects/modapi.obj", "Textures/fast_modapi.png");
	stem = new Object("3DObjects/stem.obj", "Textures/stem.png");
}

void F_Modapi::InitBuffer()
{
	hair->InitBuffer();
	head->InitBuffer();
	stem->InitBuffer();
}

void F_Modapi::InitTexture()
{
	hair->InitTexture();
	head->InitTexture();
	stem->InitTexture();
}

void F_Modapi::Render()
{
	hair->Render();
	head->Render();
	stem->Render();
}