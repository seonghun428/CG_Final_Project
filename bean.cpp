#include "bean.h"

Bean::Bean(int mx, int my)
{
	body = new Object("3DObjects/bean.obj", "Textures/gold.png");
	elements.push_back(body);
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

glm::vec3 Bean::Get_Max()
{
	return body->Get_Max_O();
}

glm::vec3 Bean::Get_Min()
{
	return body->Get_Min_O();
}