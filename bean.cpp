#include "bean.h"

Bean::Bean(int mx, int my)
{
	body = new Object("3DObjects/bean.obj", "Textures/gold.png");
	x = mx;
	y = my;
}

Bean::~Bean()
{
	delete body;
}

void Bean::InitBuffer()
{
	body->InitBuffer();
}

void Bean::InitTexture()
{
	body->InitTexture();
}

void Bean::Render()
{
	body->Render();
}

void Bean::Move()
{
	go_front += 0.1f;
}

void Bean::Move_Update()
{
	body->Update_Translate_Matrix(glm::vec3(go_front, 0.0, 0.0));
}