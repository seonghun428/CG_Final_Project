#pragma once

#include "zombie.h"

class IronZombie : public Zombie
{
private:
	Object* head;

public:
	IronZombie(int line, int num);
	~IronZombie();
};