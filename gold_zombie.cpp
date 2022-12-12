#include "gold_zombie.h"

GoldZombie::GoldZombie(int line)
{
	head = new Object("3DObjects/zombie_head.obj", "Textures/gold.png");
	body = new Object("3DObjects/zombie_body.obj", "Textures/zombie.png");
	arm_left = new Object("3DObjects/zombie_arm_left.obj", "Textures/zombie.png");
	arm_right = new Object("3DObjects/zombie_arm_right.obj", "Textures/zombie.png");
	leg_left = new Object("3DObjects/zombie_leg_left.obj", "Textures/zombie.png");
	leg_right = new Object("3DObjects/zombie_leg_right.obj", "Textures/zombie.png");
	elements.push_back(head);
	elements.push_back(body);
	elements.push_back(arm_left);
	elements.push_back(arm_right);
	elements.push_back(leg_left);
	elements.push_back(leg_right);

	this->line = line;
}

GoldZombie::~GoldZombie()
{
	delete head;
	delete body;
	delete arm_left;
	delete arm_right;
	delete leg_left;
	delete leg_right;
}