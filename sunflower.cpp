#include "sunflower.h"
#include "scene.h"

Sunflower::Sunflower(int x, int y)
{
	head = new Object("3DObjects/flower.obj", "Textures/flower.png");
	stem = new Object("3DObjects/stem.obj", "Textures/stem.png");
	elements.push_back(head);
	elements.push_back(stem);
	this->x = x;
	this->y = y;
	this->cost = 5;
}

Sunflower::~Sunflower()
{
	delete head;
	delete stem;
}

void Sunflower::Move()
{
	rot -= 0.1f;
}

void Sunflower::Move_Update()
{
	head->Update_YRotate_Matrix(rot);
}

void Sunflower::Attack()
{
	extern CScene scene;
	scene.Add_Cost();
}

glm::vec3 Sunflower::Get_Max()
{
	glm::vec3 MAX = head->Get_Max_O();

	for (auto& element : elements) {
		if (MAX.x < element->Get_Max_O().x)
			MAX.x = element->Get_Max_O().x;
		if (MAX.y < element->Get_Max_O().y)
			MAX.y = element->Get_Max_O().y;
		if (MAX.z < element->Get_Max_O().z)
			MAX.z = element->Get_Max_O().z;
	}
	MAX.x += (x - 4) * 1.85f - 0.7f;
	MAX.z += (y - 3) * 1.9f;
	return MAX;
}

glm::vec3 Sunflower::Get_Min()
{
	glm::vec3 MIN = head->Get_Min_O();

	for (auto& element : elements) {
		if (MIN.x > element->Get_Min_O().x)
			MIN.x = element->Get_Min_O().x;
		if (MIN.y > element->Get_Min_O().y)
			MIN.y = element->Get_Min_O().y;
		if (MIN.z > element->Get_Min_O().z)
			MIN.z = element->Get_Min_O().z;
	}
	MIN.x += (x - 4) * 1.85f - 0.7f;
	MIN.z += (y - 3) * 1.9f;
	return MIN;
}