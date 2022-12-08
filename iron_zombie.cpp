#include "iron_zombie.h"

IronZombie::IronZombie(int line)
{
	head = new Object("3DObjects/zombie_head.obj", "Textures/iron.png");
	body = new Object("3DObjects/zombie_body.obj", "Textures/zombie.png");
	arm_left = new Object("3DObjects/zombie_arm_left.obj", "Textures/zombie.png");
	arm_right = new Object("3DObjects/zombie_arm_right.obj", "Textures/zombie.png");
	leg_left = new Object("3DObjects/zombie_leg_left.obj", "Textures/zombie.png");
	leg_right = new Object("3DObjects/zombie_leg_right.obj", "Textures/zombie.png");

	this->line = line;
}

IronZombie::~IronZombie()
{
	delete head;
	delete body;
	delete arm_left;
	delete arm_right;
	delete leg_left;
	delete leg_right;
}

void IronZombie::InitBuffer()
{
	head->InitBuffer();
	body->InitBuffer();
	arm_left->InitBuffer();
	arm_right->InitBuffer();
	leg_left->InitBuffer();
	leg_right->InitBuffer();

	head->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
	body->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
	arm_left->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
	arm_right->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
	leg_left->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
	leg_right->Update_Translate_Matrix(glm::vec3(4.0, 0.0, (line - 3) * 1.7));
}

void IronZombie::InitTexture()
{
	head->InitTexture();
	body->InitTexture();
	arm_left->InitTexture();
	arm_right->InitTexture();
	leg_left->InitTexture();
	leg_right->InitTexture();
}

void IronZombie::Move_Update()
{
	head->Update_Translate_Matrix(glm::vec3(go_front, 0.0, 0.0));
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

void IronZombie::Render()
{
	head->Render();
	body->Render();
	arm_left->Render();
	arm_right->Render();
	leg_right->Render();
	leg_left->Render();
}

void IronZombie::Move()
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