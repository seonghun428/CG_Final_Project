#include "normal_zombie.h"

NormalZombie::NormalZombie(int line)
{
	body = new Object("3DObjects/zombie_body.obj", "Textures/zombie.png");
	arm_left = new Object("3DObjects/zombie_arm_left.obj", "Textures/zombie.png");
	arm_right = new Object("3DObjects/zombie_arm_right.obj", "Textures/zombie.png");
	leg_left = new Object("3DObjects/zombie_leg_left.obj", "Textures/zombie.png");
	leg_right = new Object("3DObjects/zombie_leg_right.obj", "Textures/zombie.png");
	elements.push_back(body);
	elements.push_back(arm_left);
	elements.push_back(arm_right);
	elements.push_back(leg_left);
	elements.push_back(leg_right);

	this->line = line;
}

NormalZombie::~NormalZombie()
{
	delete body;
	delete arm_left;
	delete arm_right;
	delete leg_left;
	delete leg_right;
}

void NormalZombie::InitBuffer()
{
	body->InitBuffer();
	arm_left->InitBuffer();
	arm_right->InitBuffer();
	leg_left->InitBuffer();
	leg_right->InitBuffer();

	body->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
	arm_left->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
	arm_right->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
	leg_left->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
	leg_right->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
}

void NormalZombie::InitTexture()
{
	body->InitTexture();
	arm_left->InitTexture();
	arm_right->InitTexture();
	leg_left->InitTexture();
	leg_right->InitTexture();
}

void NormalZombie::Move_Update()
{
	body->Update_Translate_Matrix(glm::vec3(go_front, 0.0, 0.0));
	arm_left->Update_Translate_Matrix(glm::vec3(go_front, 0.0, 0.0));
	arm_right->Update_Translate_Matrix(glm::vec3(go_front, 0.0, 0.0));
	leg_left->Update_Translate_Matrix(glm::vec3(go_front, 0.0, 0.0));
	leg_right->Update_Translate_Matrix(glm::vec3(go_front, 0.0, 0.0));

	leg_left->Update_Translate_Matrix(glm::vec3(0.0, 0.6, 0.0));
	leg_left->Update_ZRotate_Matrix(leg_angle);
	leg_left->Update_Translate_Matrix(glm::vec3(0.0, -0.6, 0.0));

	leg_right->Update_Translate_Matrix(glm::vec3(0.0, 0.6, 0.0));
	leg_right->Update_ZRotate_Matrix(-leg_angle);
	leg_right->Update_Translate_Matrix(glm::vec3(0.0, -0.6, 0.0));
}

void NormalZombie::Attack_Update()
{
	arm_left->Update_Translate_Matrix(glm::vec3(0.0, 1.1, 0.0));
	arm_left->Update_ZRotate_Matrix(arm_angle);
	arm_left->Update_Translate_Matrix(glm::vec3(0.0, -1.1, 0.0));

	arm_right->Update_Translate_Matrix(glm::vec3(0.0, 1.1, 0.0));
	arm_right->Update_ZRotate_Matrix(arm_angle);
	arm_right->Update_Translate_Matrix(glm::vec3(0.0, -1.1, 0.0));
}

void NormalZombie::Render()
{
	body->Render();
	arm_left->Render();
	arm_right->Render();
	leg_right->Render();
	leg_left->Render();
}

glm::vec3 NormalZombie::Get_Max()
{
	glm::vec3 MAX = body->Get_Max_O();

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

glm::vec3 NormalZombie::Get_Min()
{
	glm::vec3 MIN = body->Get_Min_O();

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

void NormalZombie::Move()
{
	if (leg_up)
		leg_angle += 5.0f;
	else
		leg_angle -= 5.0f;

	if (leg_angle >= 40.0f)
		leg_up = false;
	else if (leg_angle <= -40.0f)
		leg_up = true;

	go_front -= 0.02f;
}

void NormalZombie::Attack()
{
	if (arm_up)
		arm_angle += 10.0f;
	else
		arm_angle -= 10.0f;

	if (arm_angle >= 10.0f)
		arm_up = false;
	else if (arm_angle <= -80.0f)
		arm_up = true;
}