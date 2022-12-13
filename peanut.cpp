#include "peanut.h"

Peanut::Peanut(int x, int y)
{
	body = new Object("3DObjects/peanut.obj", "Textures/peanut.png");
	elements.push_back(body);
	this->x = x;
	this->y = y;
}

Peanut::~Peanut()
{
	delete body;
}

glm::vec3 Peanut::Get_Max()
{
	return body->Get_Max_O();
}

glm::vec3 Peanut::Get_Min()
{
	return body->Get_Min_O();
}