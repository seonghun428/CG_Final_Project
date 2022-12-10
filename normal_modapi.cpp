#include "normal_modapi.h"
#include "bean.h"

Modapi::Modapi()
{
	head = new Object("3DObjects/modapi.obj", "Textures/modapi.png");
	stem = new Object("3DObjects/stem.obj", "Textures/stem.png");
}

void Modapi::InitBuffer()
{
	head->InitBuffer();
	stem->InitBuffer();
}

void Modapi::InitTexture()
{
	head->InitTexture();
	stem->InitTexture();
}

void Modapi::Render()
{
	head->Render();
	stem->Render();
}

extern list<Model*> objects;

void Modapi::Attack()
{
	Model* bean = new Bean();
	bean->InitTexture();
	objects.push_back(bean);
}