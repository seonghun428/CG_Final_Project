#include "peanut.h"

Peanut::Peanut()
{
	body = new Object("3DObjects/peanut.obj", "Textures/peanut.png");
	elements.push_back(body);
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

glm::vec3 Peanut::Get_Max()
{
	return body->Get_Max_O();
}

glm::vec3 Peanut::Get_Min()
{
	return body->Get_Min_O();
}