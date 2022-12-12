#pragma once

#include "zombie.h"

class GoldZombie : public Zombie
{
private:
	Object* head;

public:
	GoldZombie(int line);
	~GoldZombie();
};