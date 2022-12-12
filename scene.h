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
#include "mower.h"
#include "plane.h"
#include "display.h"
#include "wall.h"

#include "world.h"

#define BEGIN 100
#define MAIN 101
#define WIN 102
#define LOSE 103

class CScene
{
private:
	Shader shader;

	Model* display;
	Model* back_wall;
	Model* front_wall;
	Model* mower1;
	Model* mower2;
	Model* mower3;
	Model* mower4;
	Model* mower5;

	Model* plane;
	Model* cherry;
	Model* zombie;

	GLenum polymod = GL_FILL;

	int state;

	glm::mat4 projection = glm::mat4(1.0f);
	unsigned int projectionLocation;

public:
	CScene();
	~CScene();

	World world;

	int Get_state() { return state; }
	
	void Init_Begin();
	void Init_Select();
	void Init_Main();
	void Init_Win();
	void Init_Lose();

	void Render();
	void Update();
	void Update2();

	void Input(unsigned char key);
	void Input_s(int key);
};