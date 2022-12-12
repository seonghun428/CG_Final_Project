#include "bean.h"

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
	return body->Get_Max_O();
}

glm::vec3 Bean::Get_Min()
{
	return body->Get_Min_O();
}