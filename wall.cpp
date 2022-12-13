#include "wall.h"
#include "scene.h"

Wall::Wall(int a) 
{
	if (a == 0) body = new Object("3DObjects/back_wall.obj", "Textures/gold.png");
	else if (a == 1) body = new Object("3DObjects/front_wall.obj", "Textures/gold.png");
	elements.push_back(body);
}

Wall::~Wall() 
{ 
	delete body; 
}

glm::vec3 Wall::Get_Max()
{
	glm::vec3 MAX;
	MAX = body->Get_Max_O();
	//cout << MAX.x << MAX.y << MAX.z << endl;
	return MAX;
}

glm::vec3 Wall::Get_Min()
{ 
	glm::vec3 MIN;
	MIN = body->Get_Min_O();
	return MIN;
}

void Wall::Get_Collide(Model* other, string group)
{
	/*if (group == "wall:zombie")
	{
		extern CScene scene;
		scene.Init_Lose();
	}*/
}