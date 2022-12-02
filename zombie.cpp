#include "zombie.h"

void Zombie::InitBuffer()
{
	body.InitBuffer();
	arm_left.InitBuffer();
	arm_right.InitBuffer();
	leg_left.InitBuffer();
	leg_right.InitBuffer();
}

void Zombie::Update()
{
	body.Update_Synthetic_Matrix();
	arm_left.Update_Synthetic_Matrix();
	arm_right.Update_Synthetic_Matrix();
	leg_left.Update_Synthetic_Matrix();
	leg_right.Update_Synthetic_Matrix();
}

void Zombie::Render()
{
	body.Render();
	arm_left.Render();
	arm_right.Render();
	leg_left.Render();
	leg_right.Render();
}

void Zombie::Move()
{
	//body.Update_Translate_Matrix();
	//arm_left.Update_Translate_Matrix();
	//arm_right.Update_Translate_Matrix();
	if (leg_up)
		leg_angle += 5.0f;
	else
		leg_angle -= 5.0f;

	if (leg_angle >= 30.0f)
		leg_up = false;
	else if (leg_angle <= -30.0f)
		leg_up = true;
	
	leg_left.Update_ZRotate_Matrix(leg_angle);
	leg_right.Update_ZRotate_Matrix(-leg_angle);

	//leg_left.Update_Translate_Matrix();
	//leg_right.Update_Translate_Matrix();
}