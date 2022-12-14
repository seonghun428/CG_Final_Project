#include "cherry.h"
#include "scene.h"

Cherry::Cherry(int x, int y)
{
	body = new Object("3DObjects/cherry.obj", "Textures/cherry.png");
	elements.push_back(body);
	this->x = x;
	this->y = y;
	this->cost = 20;
	this->hp = 200;
}

Cherry::~Cherry()
{
	delete body;
}

void Cherry::Move()
{
	scale.x += 0.02f;
	scale.y += 0.02f;
	scale.z += 0.02f;

	if (scale.x >= 1.92f)
	{
		if (cnt == 0)
		{
			delete body;
			elements.clear();
			body = new Object("3DObjects/bomb.obj", "Textures/boom.png");
			body->InitTexture();
			elements.push_back(body);
			crash = true;
			cnt = 1;
		}
	}

	if (scale.x >= 2.0f)
	{
		extern CScene scene;
		scene.world.remove_object(this);
		return;
	}
}

void Cherry::Move_Update()
{
	body->Update_Scale_Matrix(scale);
}

glm::vec3 Cherry::Get_Max()
{
	glm::vec3 MAX = body->Get_Max_O();

	MAX.x *= 3.0f;
	MAX.y *= 3.0f;
	MAX.z *= 3.0f;

	MAX.x += (x - 4) * 1.85 - 0.7f;
	MAX.z += (y - 3) * 1.9;
	return MAX;
}

glm::vec3 Cherry::Get_Min()
{
	glm::vec3 MIN = body->Get_Min_O();

	MIN.x *= 3.0f;
	MIN.y *= 3.0f;
	MIN.z *= 3.0f;

	MIN.x += (x - 4) * 1.85 - 0.7f;
	MIN.z += (y - 3) * 1.9;
	return MIN;
}