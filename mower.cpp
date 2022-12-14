#include "mower.h"

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
		element->Update_Translate_Matrix(glm::vec3(-8.5, 0.0, (line - 3) * 1.9));
	}
}

glm::vec3 Mower::Get_Max()
{
	glm::vec3 MAX = body->Get_Max_O();
	MAX.x -= 8.5f;
	MAX.z += (line - 3) * 1.9;
	return MAX;
}

glm::vec3 Mower::Get_Min()
{
	glm::vec3 MIN = body->Get_Min_O();
	MIN.x -= 8.5f;
	MIN.z += (line - 3) * 1.9;
	return MIN;
}