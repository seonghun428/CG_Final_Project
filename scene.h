#pragma once

#include "Shader.h"
#include "normal_zombie.h"
#include "iron_zombie.h"
#include "gold_zombie.h"
#include "peanut.h"
#include "cherry.h"
#include "slow_modapi.h"
#include "fast_modapi.h"
#include "penetrate_modapi.h"
#include "sunflower.h"
#include "bean.h"
#include "plane.h"
#include "world.h"

class Scene
{
private:
	Shader shader;

	Model* plane;
	Model* cherry;
	Model* zombie;

public:
	Scene();
	~Scene();

	World world;

	void Init_Begin();
	void Init_Select();
	void Init_Main();
	void Init_End();

	void Render();
};