#include "mower.h"

Mower::Mower() {}
Mower::Mower(int line)
{
	body = new Object("3DObjects/mower.obj", "Textures/mower.png");
	elements.push_back(body);

	this->line = line;
}

Mower::~Mower()
{
	delete body;
}

void Mower::InitBuffer()
{
	for (auto& element : elements)
	{
		element->InitBuffer();
		element->Update_Translate_Matrix(glm::vec3(-8.0, 0.0, (line - 3) * 1.7));
	}
}

glm::vec3 Mower::Get_Max()
{
	glm::vec3 MAX = body->Get_Max_O();

	for (auto& element : elements) {
		if (MAX.x < element->Get_Max_O().x)
			MAX.x = element->Get_Max_O().x;
		if (MAX.y < element->Get_Max_O().y)
			MAX.y = element->Get_Max_O().y;
		if (MAX.z < element->Get_Max_O().z)
			MAX.z = element->Get_Max_O().z;
	}


	return MAX;
}

glm::vec3 Mower::Get_Min()
{
	glm::vec3 MIN = body->Get_Min_O();

	for (auto& element : elements) {
		if (MIN.x > element->Get_Min_O().x)
			MIN.x = element->Get_Min_O().x;
		if (MIN.y > element->Get_Min_O().y)
			MIN.y = element->Get_Min_O().y;
		if (MIN.z > element->Get_Min_O().z)
			MIN.z = element->Get_Min_O().z;
	}

	return MIN;
}