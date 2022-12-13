#include "bean.h"
#include "scene.h"

Bean::Bean(int mx, int my, string imgfile)
{
	body = new Object("3DObjects/bean.obj", imgfile);
	elements.push_back(body);
	x = mx;
	y = my;
}

Bean::~Bean()
{
	delete body;
	elements.clear();
	body = nullptr;
}

void Bean::Move()
{
	go_front += 0.1f;
}

void Bean::Move_Update()
{
	body->Update_Translate_Matrix(glm::vec3(go_front, 0.0, 0.0));
}

glm::vec3 Bean::Get_Max()
{
	if (body == nullptr) return glm::vec3(-10000.0, -10000.0, -10000.0);
	glm::vec3 MAX = body->Get_Max_O();
	MAX.x += go_front;
	return MAX;
}

glm::vec3 Bean::Get_Min()
{
	if (body == nullptr) return glm::vec3(-10000.0, -10000.0, -10000.0);
	glm::vec3 MIN = body->Get_Min_O();
	MIN.x += go_front;
	return MIN;
}

void Bean::Get_Collide(Model* other, string group)
{
	if (group == "bean:zombie" || group == "bean:wall")
	{
		extern CScene scene;
		scene.world.remove_object(this);
	}
}