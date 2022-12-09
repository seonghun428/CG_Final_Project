#include "penetrate_modapi.h"

P_Modapi::P_Modapi()
{
	hair = new Object("3DObjects/leaf_3.obj", "Textures/penetrate_leaf.png");
	head = new Object("3DObjects/modapi.obj", "Textures/penetrate_modapi.png");
	stem = new Object("3DObjects/stem.obj", "Textures/penetrate_stem.png");
}

void P_Modapi::InitBuffer()
{
	hair->InitBuffer();
	head->InitBuffer();
	stem->InitBuffer();
}

void P_Modapi::InitTexture()
{
	hair->InitTexture();
	head->InitTexture();
	stem->InitTexture();
}

void P_Modapi::Render()
{
	hair->Render();
	head->Render();
	stem->Render();
}