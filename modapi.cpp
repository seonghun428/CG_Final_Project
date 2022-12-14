#include "modapi.h"
#include "bean.h"
#include "scene.h"

Modapi::Modapi(int x, int y)
{
	head = new Object("3DObjects/modapi.obj", "Textures/modapi.png");
	stem = new Object("3DObjects/stem.obj", "Textures/stem.png");
	elements.push_back(head);
	elements.push_back(stem);
	this->x = x;
	this->y = y;
	this->cost = 5;
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
	MAX.x += (x - 4) * 1.85 - 0.7f;
	MAX.z += (y - 3) * 1.9;
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
	MIN.x += (x - 4) * 1.85 - 0.7f;
	MIN.z += (y - 3) * 1.9;
	return MIN;
}

void Modapi::Attack()
{
	Model* bean = new Bean(this->x,this->y,"Textures/modapi.png");
	bean->InitTexture();
	bean->set_state(1);
	extern CScene scene;

	scene.world.add_object(bean);
	scene.world.add_tuple(bean);
	scene.world.add_tuple2(bean);
	tuple<list<Model*>, list<Model*>> group = scene.world.get_group();
	tuple<list<Model*>, list<Model*>> group2 = scene.world.get_group2();
	scene.world.add_collision_group("bean:zombie", group);
	scene.world.add_collision_group("bean:wall", group2);
}