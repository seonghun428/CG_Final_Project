#include "zombie.h"

Zombie::Zombie()
{
	body = new Cube("3DObjects/zombie_body.obj");
	arm_left = new Cube("3DObjects/zombie_arm_left.obj");
	arm_right = new Cube("3DObjects/zombie_arm_right.obj");
	leg_left = new Cube("3DObjects/zombie_leg_left.obj");
	leg_right = new Cube("3DObjects/zombie_leg_right.obj");
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
	leg_right->InitBuffer();
	leg_left->InitBuffer();

	body->Update_Synthetic_Matrix();
	arm_left->Update_Synthetic_Matrix();
	arm_right->Update_Synthetic_Matrix();
	leg_right->Update_Synthetic_Matrix();
	leg_left->Update_Synthetic_Matrix();
}

void Zombie::Move_Update()
{
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
}