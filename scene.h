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
#include "sun.h"

#include "world.h"

#define BEGIN 100
#define MAIN 101
#define WIN 102
#define LOSE 103

class CScene
{
private:
	Model* display1 = new Display("Textures/main.png");
	Model* display2 = new Display("Textures/win.png");
	Model* display3 = new Display("Textures/lose.png");
	Model* display4 = new Display("Textures/ui.png");

	Model* back_wall = new Wall(0);
	Model* front_wall = new Wall(1);
	Model* mower1 = new Mower(1);
	Model* mower2 = new Mower(2);
	Model* mower3 = new Mower(3);
	Model* mower4 = new Mower(4);
	Model* mower5 = new Mower(5);

	Model* plane = new Plane();

	Model* sun = new Sun();

	list<Model*> mowers;
	list<Model*> plants;
	list<Model*> zombies;

	glm::vec3 lightpos = glm::vec3(-21.0, 0.0, 0.0);

	GLenum polymod = GL_FILL;

	int state;

	int cur_cost;

	bool select_mode = false;
	int selected_plant = 0;

	glm::mat4 projection = glm::mat4(1.0f);
	unsigned int projectionLocation;

public:
	CScene();
	~CScene();

	World world;
	Shader shader;

	int Get_state() { return state; }
	
	void Init_Textures();

	void Init_Begin();
	void Init_Main();
	void Init_Win();
	void Init_Lose();

	void Render();
	void Update();
	void Update2();
	void Update3();

	void Input(unsigned char key);
	void Input_s(int key);
	void mouse(int button, int state, int mx, int my);

	bool collide(Model* a, Model* b);
};