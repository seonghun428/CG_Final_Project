#include "peanut.h"

Peanut::Peanut(int x, int y)
{
	body = new Object("3DObjects/peanut.obj", "Textures/peanut.png");
	elements.push_back(body);
	this->x = x;
	this->y = y;
	this->cost = 10;
}

Peanut::~Peanut()
{
	delete body;
}

glm::vec3 Peanut::Get_Max()
{
	glm::vec3 MAX = body->Get_Max_O();
	MAX.x += (x - 4) * 1.85 - 0.7f;
	MAX.z += (y - 3) * 1.9;
	return MAX;
}

glm::vec3 Peanut::Get_Min()
{
	glm::vec3 MIN = body->Get_Min_O();
	MIN.x += (x - 4) * 1.85 - 0.7f;
	MIN.z += (y - 3) * 1.9;
	return MIN;
}