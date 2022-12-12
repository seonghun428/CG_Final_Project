#pragma once

#include "Shader.h"

#include "zombie.h"
#include "iron_zombie.h"
#include "gold_zombie.h"
#include "peanut.h"
#include "cherry.h"
#include "modapi.h"
#include "slow_modapi.h"
#include "fast_modapi.h"
#include "penetrate_modapi.h"
#include "sunflower.h"
#include "bean.h"
#include "plane.h"

#include "world.h"

class CScene
{
private:
	Shader shader;

	Model* plane;
	Model* cherry;
	Model* zombie;

	GLenum polymod = GL_FILL;

public:
	CScene();
	~CScene();

	World world;

	void Init_Begin();
	void Init_Select();
	void Init_Main();
	void Init_End();

	void Render();
	void Update();
	void Update2();

	void Input(unsigned char key);
	void Input_s(int key);
};