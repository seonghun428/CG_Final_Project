#include "zombie.h"

Zombie::Zombie(int line)
{
	body = new Cube("3DObjects/zombie_body.obj", "Textures/test.png");
	arm_left = new Cube("3DObjects/zombie_arm_left.obj", "Textures/test.png");
	arm_right = new Cube("3DObjects/zombie_arm_right.obj", "Textures/test.png");
	leg_left = new Cube("3DObjects/zombie_leg_left.obj", "Textures/test.png");
	leg_right = new Cube("3DObjects/zombie_leg_right.obj", "Textures/test.png");

	this->line = line;
}

Zombie::~Zombie()
{
	delete body;
	delete arm_left;
	delete arm_right;
	delete leg_left;
	delete leg_right;
}

void Zombie::InitBuffer()
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

void Zombie::InitTexture()
{
	body->InitTexture();
	arm_left->InitTexture();
	arm_right->InitTexture();
	leg_left->InitTexture();
	leg_right->InitTexture();
}

void Zombie::Move_Update()
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

void Zombie::Render()
{
	body->Render();
	arm_left->Render();
	arm_right->Render();
	leg_right->Render();
	leg_left->Render();
}

void Zombie::Move()
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