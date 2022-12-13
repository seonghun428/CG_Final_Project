#include "cherry.h"

Cherry::Cherry(int x, int y)
{
	body = new Object("3DObjects/cherry.obj", "Textures/cherry.png");
	elements.push_back(body);
	this->x = x;
	this->y = y;
}

Cherry::~Cherry()
{
	delete body;
}


glm::vec3 Cherry::Get_Max()
{
	return body->Get_Max_O();
}

glm::vec3 Cherry::Get_Min()
{
	return body->Get_Min_O();
}