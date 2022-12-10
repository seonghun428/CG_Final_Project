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

void Modapi::Attack()
{
	Model* bean = new Bean(0,0);
	bean->InitTexture();
	scene.world.add_object(bean);
}