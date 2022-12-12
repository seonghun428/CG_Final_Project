#include "cherry.h"

Cherry::Cherry()
{
	body = new Object("3DObjects/cherry.obj", "Textures/cherry.png");
	elements.push_back(body);
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