#include "modapi.h"
#include "bean.h"
#include "scene.h"

Modapi::Modapi()
{
	head = new Object("3DObjects/modapi.obj", "Textures/modapi.png");
	stem = new Object("3DObjects/stem.obj", "Textures/stem.png");
	elements.push_back(head);
	elements.push_back(stem);
}

Modapi::~Modapi()
{
	delete head;
	delete stem;
}

glm::vec3 Modapi::Get_Max()
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


	return MAX;
}

glm::vec3 Modapi::Get_Min()
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

	return MIN;
}

void Modapi::Attack()
{
	Model* bean = new Bean(0,0);
	bean->InitTexture();
	extern CScene scene;
	scene.world.add_object(bean);
}