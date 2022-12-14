#include "penetrate_modapi.h"
#include "bean.h"
#include "scene.h"

P_Modapi::P_Modapi(int x, int y)
{
	hair = new Object("3DObjects/leaf_3.obj", "Textures/penetrate_leaf.png");
	head = new Object("3DObjects/modapi.obj", "Textures/penetrate_modapi.png");
	stem = new Object("3DObjects/stem.obj", "Textures/penetrate_stem.png");
	elements.push_back(hair);
	elements.push_back(head);
	elements.push_back(stem);
	this->x = x;
	this->y = y;
	this->cost = 20;
}

P_Modapi::~P_Modapi()
{
	delete hair;
	delete head;
	delete stem;
}

glm::vec3 P_Modapi::Get_Max()
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

glm::vec3 P_Modapi::Get_Min()
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

void P_Modapi::Attack()
{
	Model* bean = new Bean(this->x, this->y, "Textures/penetrate_leaf.png");
	bean->InitTexture();
	bean->set_state(3);
	extern CScene scene;

	scene.world.add_object(bean);
	scene.world.add_tuple(bean);
	scene.world.add_tuple2(bean);
	tuple<list<Model*>, list<Model*>> group = scene.world.get_group();
	tuple<list<Model*>, list<Model*>> group2 = scene.world.get_group2();
	scene.world.add_collision_group("bean:zombie", group);
	scene.world.add_collision_group("bean:wall", group2);
}