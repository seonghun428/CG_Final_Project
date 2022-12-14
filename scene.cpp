#include "scene.h"

CScene::CScene() {}
CScene::~CScene() {}

void CScene::Init_Textures()
{
	display1->InitTexture();
	display2->InitTexture();
	display3->InitTexture();
	display4->InitTexture();
	back_wall->InitTexture();
	front_wall->InitTexture();
	mower1->InitTexture();
	mower2->InitTexture();
	mower3->InitTexture();
	mower4->InitTexture();
	mower5->InitTexture();
	plane->InitTexture();
	sun->InitTexture();
}

void CScene::Init_Begin()
{
	state = BEGIN;

	world.clear();

	world.add_object(display1);

	projection = glm::mat4(1.0f);
	projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	world.setting(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-300.0, -400.0, 500.0));
}

void CScene::Init_Main()
{
	state = MAIN;

	world.clear();
	zombies.clear();
	mowers.clear();
	plants.clear();

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> line(1, 5);
	uniform_int_distribution<int> kind(1, 3);
	uniform_int_distribution<int> x(1, 30);

	/*for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (j >= 0 && j < 6)
			{
				Model* zombie = new Zombie(i + 1, j + 1);
				zombie->InitTexture();
				zombies.push_back(zombie);
			}
			else if (j >= 6 && j < 13)
			{
				Model* zombie = new IronZombie(i + 1, j + 1);
				zombie->InitTexture();
				zombies.push_back(zombie);
			}
			else if (j >= 13 && j < 20)
			{
				Model* zombie = new GoldZombie(i + 1, j + 1);
				zombie->InitTexture();
				zombies.push_back(zombie);
			}
		}
	}*/

	for (int i = 0; i < 100; ++i) {
		if (kind(rd) == 1) {
			Model* zombie = new Zombie(line(rd), x(rd));
			zombie->InitTexture();
			zombies.push_back(zombie);
		}

		else if(kind(rd) == 2) {
			Model* zombie = new IronZombie(line(rd), x(rd));
			zombie->InitTexture();
			zombies.push_back(zombie);
		}

		else if(kind(rd) == 3) {
			Model* zombie = new GoldZombie(line(rd), x(rd));
			zombie->InitTexture();
			zombies.push_back(zombie);
		}
	}
	
	world.add_object(zombies);

	world.add_collision_group("wall:zombie", back_wall, zombies);
	
	world.add_tuple(zombies);
	world.add_tuple2(front_wall);

	world.add_object(plane);

	mowers.push_back(mower1);
	mowers.push_back(mower2);
	mowers.push_back(mower3);
	mowers.push_back(mower4);
	mowers.push_back(mower5);

	world.add_object(mowers);

	world.add_collision_group("mower:zombie", make_tuple(mowers, zombies));
	world.add_collision_group("mower:wall", front_wall, mowers);

	world.add_object(sun);

	cur_cost = 15;
}

void CScene::Init_Win()
{
	state = WIN;

	world.clear();

	world.add_object(display2);

	projection = glm::mat4(1.0f);
	projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	world.setting(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 5.0, 10.0));
}

void CScene::Init_Lose()
{
	world.clear();
	state = LOSE;
	world.add_object(display3);

	projection = glm::mat4(1.0f);
	projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	world.setting(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 0.0, 500.0));
}

void CScene::Render()
{
	glClearColor(0.0f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

	glViewport(0, 0, 800, 800);

	if (state == MAIN)
	{
		projection = glm::mat4(1.0f);

		if (select_mode)
		{
			projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);

			projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
			glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

			world.setting(glm::vec3(0.0f, 9.9f, 3.0f), glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), lightpos);
		}
		else
		{
			projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
			projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));

			projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
			glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

			world.setting(glm::vec3(0.0f, 7.0f, 20.0f), glm::vec3(0.0f, -4.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), lightpos);
		}
	}

	glPolygonMode(GL_FRONT_AND_BACK, polymod);
	for (auto& object : world.all_object())
	{
		object->InitBuffer();
		object->Move_Update();
		object->Attack_Update();
		object->Render();
	}

	if (state == MAIN)
	{
		glViewport(550, 600, 200, 200);

		const string str1 = "COST: ";
		string str2 = to_string(cur_cost);
		string str = str1 + str2;

		glRasterPos2f(0.0f, 0.0f);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)str.c_str());

		glViewport(0, -600, 800, 800);

		projection = glm::mat4(1.0f);
		projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

		projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

		world.setting(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 5.0, 10.0));

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		display4->InitBuffer();
		display4->Render();		
	}
	
	glutSwapBuffers();
}

void CScene::Update()
{
	for (auto group : world.all_collision_group())
	{
		for (auto a : get<0>(group.second))
		{
			for (auto b : get<1>(group.second))
			{
				if (collide(a, b))
				{
					if (group.first == "wall:zombie")
					{
						Init_Lose();
						return;
					}
					a->Get_Collide(b, group.first);
					b->Get_Collide(a, group.first);
				}
			}
		}
	}
}

void CScene::Update2()
{
	for (auto& object : world.all_object())
	{
		object->Move();

		if (object == dynamic_cast<Zombie*>(object))
			object->Attack();
	}

	lightpos = glm::vec3(-21.0, 0.0, 0.0);
	glm::mat4 rt = glm::mat4(1.0f);

	rt = glm::rotate(rt, glm::radians(sun->Get_z_rot()), glm::vec3(0.0, 0.0, 1.0));
	lightpos = rt * glm::vec4(lightpos, 1.0);

	if (sun->Get_z_rot() <= -180.0f)
	{
		sun->Set_z_rot(0.0f);
		Init_Win();
	}
}

void CScene::Update3()
{
	for (auto& object : world.all_object())
	{
		if (object == dynamic_cast<Plant*>(object))
			object->Attack();
	}
}

void CScene::Input(unsigned char key)
{
	switch (key) {
	case 'w':
	case 'W':
		if (polymod == GL_FILL)	polymod = GL_LINE;
		else polymod = GL_FILL;
		break;

	case 'x':
	case 'X':
		break;

	case 'y':
	case 'Y':
		break;

	case 's':
	case 'S':
		break;
	}
}

void CScene::Input_s(int key)
{
	switch (key) {
	case GLUT_KEY_UP:
		world.setting(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 100.0, 0.0));
		break;

	case GLUT_KEY_DOWN:
		world.setting(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 100.0, 0.0));
		break;

	case GLUT_KEY_LEFT:
		world.setting(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 100.0, 0.0));
		break;

	case GLUT_KEY_RIGHT:
		world.setting(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 100.0, 0.0));
		break;
	}
}

void CScene::mouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (this->state == MAIN)
		{
			if (select_mode)
			{
				for (int i = 0; i < 5; ++i)
				{
					for (int j = 0; j < 9; ++j)
					{
						if (mx >= j * 75 + 100 && mx < (j + 1) * 75 + 100)
						{
							if (my >= i * 80 + 80 && my < (i + 1) * 80 + 80)
							{
								if (selected_plant == 1)
								{

									Model* sunflower = new Sunflower(j + 1, i + 1);
									if (cur_cost >= sunflower->Get_Cost()) {
										sunflower->InitTexture();
										plants.push_back(sunflower);
										world.add_object(sunflower);
										cur_cost -= sunflower->Get_Cost();
									}

									else
										delete sunflower;
								}
								else if (selected_plant == 2)
								{
									Model* modapi = new Modapi(j + 1, i + 1);
									if (cur_cost >= modapi->Get_Cost()) {
										modapi->InitTexture();
										plants.push_back(modapi);
										world.add_object(modapi);
										cur_cost -= modapi->Get_Cost();
									}

									else
										delete modapi;
								}
								else if (selected_plant == 3)
								{
									Model* s_modapi = new S_Modapi(j + 1, i + 1);
									if (cur_cost >= s_modapi->Get_Cost()) {
										s_modapi->InitTexture();
										plants.push_back(s_modapi);
										world.add_object(s_modapi);
										cur_cost -= s_modapi->Get_Cost();
									}

									else
										delete s_modapi;
								}
								else if (selected_plant == 4)
								{
									Model* f_modapi = new F_Modapi(j + 1, i + 1);
									if (cur_cost >= f_modapi->Get_Cost()) {
										f_modapi->InitTexture();
										plants.push_back(f_modapi);
										world.add_object(f_modapi);
										cur_cost -= f_modapi->Get_Cost();
									}

									else
										delete f_modapi;
								}
								else if (selected_plant == 5)
								{
									Model* p_modapi = new P_Modapi(j + 1, i + 1);
									if (cur_cost >= p_modapi->Get_Cost()) {
										p_modapi->InitTexture();
										plants.push_back(p_modapi);
										world.add_object(p_modapi);
										cur_cost -= p_modapi->Get_Cost();
									}

									else
										delete p_modapi;
								}
								else if (selected_plant == 6)
								{
									Model* peanut = new Peanut(j + 1, i + 1);
									if (cur_cost >= peanut->Get_Cost()) {
										peanut->InitTexture();
										plants.push_back(peanut);
										world.add_object(peanut);
										cur_cost -= peanut->Get_Cost();
									}

									else
										delete peanut;
								}
								else if (selected_plant == 7)
								{
									Model* cherry = new Cherry(j + 1, i + 1);
									if (cur_cost >= cherry->Get_Cost()) {
										cherry->InitTexture();
										cherries.push_back(cherry);
										world.add_object(cherry);
										cur_cost -= cherry->Get_Cost();
									}

									else
										delete cherry;
								}

								world.add_collision_group("plant:zombie", make_tuple(plants, zombies));
								world.add_collision_group("cherry:zombie", make_tuple(cherries, zombies));
								select_mode = false;
								selected_plant = 0;
								break;
							}
						}						
					}
				}
			}
			else
			{
				if (my >= 615 && my < 785)
				{
					if (mx >= 10 && mx < 100)
					{
						selected_plant = 1;
						select_mode = true;
					}
					else if (mx >= 120 && mx < 210)
					{
						selected_plant = 2;
						select_mode = true;
					}
					else if (mx >= 230 && mx < 325)
					{
						selected_plant = 3;
						select_mode = true;
					}
					else if (mx >= 345 && mx < 435)
					{
						selected_plant = 4;
						select_mode = true;
					}
					else if (mx >= 460 && mx < 550)
					{
						selected_plant = 5;
						select_mode = true;
					}
					else if (mx >= 580 && mx < 670)
					{
						selected_plant = 6;
						select_mode = true;
					}
					else if (mx >= 695 && mx < 785)
					{
						selected_plant = 7;
						select_mode = true;
					}
				}
			}
		}
	}
}

bool CScene::collide(Model* a, Model* b)
{
	if (a == nullptr || b == nullptr) return false;
	if (a->Get_Max().x < b->Get_Min().x || a->Get_Min().x > b->Get_Max().x) return false;
	if (a->Get_Max().y < b->Get_Min().y || a->Get_Min().y > b->Get_Max().y) return false;
	if (a->Get_Max().z < b->Get_Min().z || a->Get_Min().z > b->Get_Max().z) return false;

	return true;
}