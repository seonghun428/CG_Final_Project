#include "iron_zombie.h"

IronZombie::IronZombie(int line, int num)
{
	head = new Object("3DObjects/zombie_head.obj", "Textures/iron.png");
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
	this->num = num;
	this->hp = 5;
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