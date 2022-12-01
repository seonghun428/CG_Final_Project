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