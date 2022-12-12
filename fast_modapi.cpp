#include "fast_modapi.h"

F_Modapi::F_Modapi()
{
	hair = new Object("3DObjects/leaf_2.obj", "Textures/leaf.png");
	head = new Object("3DObjects/modapi.obj", "Textures/fast_modapi.png");
	stem = new Object("3DObjects/stem.obj", "Textures/stem.png");
	elements.push_back(hair);
	elements.push_back(head);
	elements.push_back(stem);
}

void F_Modapi::InitBuffer()
{
	hair->InitBuffer();
	head->InitBuffer();
	stem->InitBuffer();
}

void F_Modapi::InitTexture()
{
	hair->InitTexture();
	head->InitTexture();
	stem->InitTexture();
}

void F_Modapi::Render()
{
	hair->Render();
	head->Render();
	stem->Render();
}

glm::vec3 F_Modapi::Get_Max()
{
	glm::vec3 MAX = hair->Get_Max_O();

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

glm::vec3 F_Modapi::Get_Min()
{
	glm::vec3 MIN = hair->Get_Min_O();

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