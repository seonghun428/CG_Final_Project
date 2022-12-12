#include "slow_modapi.h"

S_Modapi::S_Modapi()
{
	hair = new Object("3DObjects/leaf_1.obj", "Textures/leaf.png");
	head = new Object("3DObjects/modapi.obj", "Textures/slow_modapi.png");
	stem = new Object("3DObjects/stem.obj", "Textures/stem.png");
	elements.push_back(hair);
	elements.push_back(head);
	elements.push_back(stem);
}

void S_Modapi::InitBuffer()
{
	hair->InitBuffer();
	head->InitBuffer();
	stem->InitBuffer();
}

void S_Modapi::InitTexture()
{
	hair->InitTexture();
	head->InitTexture();
	stem->InitTexture();
}

void S_Modapi::Render()
{
	hair->Render();
	head->Render();
	stem->Render();
}