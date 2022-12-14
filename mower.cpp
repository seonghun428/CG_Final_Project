#include "mower.h"
#include "scene.h"

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

void Mower::Move()
{
	if (crash)
		go_front += 0.1f;
}

void Mower::Move_Update()
{
	for (auto& element : elements)
	{
		element->Update_Translate_Matrix(glm::vec3(go_front, 0.0, 0.0));
	}
}

glm::vec3 Mower::Get_Max()
{
	glm::vec3 MAX = body->Get_Max_O();
	MAX.x += go_front - 8.5f;
	MAX.z += (line - 3) * 1.9f;
	return MAX;
}

glm::vec3 Mower::Get_Min()
{
	glm::vec3 MIN = body->Get_Min_O();
	MIN.x += go_front - 8.5f;
	MIN.z += (line - 3) * 1.9f;
	return MIN;
}

void Mower::Get_Collide(Model* other, string group) 
{
	if (group == "mower:zombie")
	{
		if (cnt == 0)
		{
			crash = true;
			cnt = 1;
		}
	}
	else if (group == "mower:wall")
	{
		extern CScene scene;
		scene.world.remove_object(this);
		crash = false;
		return;
	}
}