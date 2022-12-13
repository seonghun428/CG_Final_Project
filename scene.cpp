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

void CScene::Init_Select()
{

}

void CScene::Init_Main()
{
	state = MAIN;

	world.clear();

	//cherry = new Cherry();

	/*for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			Model* zombie = new Zombie(i + 1, j + 1);
			world.add_object(zombie);
		}
	}*/

	//world.add_object(cherry);

	//world.add_object(zombie);

	//world.add_collision_group("cherry:zombie", cherry, zombie);
	//world.add_collision_group("modapi:zombie", modapi, zombie);
	//world.add_collision_group("wall:zombie", back_wall, zombie);
	//world.add_tuple(zombie);
	//world.add_tuple2(front_wall);

	/*for (auto& object : world.all_object())
	{
		object->InitTexture();
	}*/

	world.add_object(plane);

	world.add_object(mower1);
	world.add_object(mower2);
	world.add_object(mower3);
	world.add_object(mower4);
	world.add_object(mower5);

	//world.add_collision_group("mower:zombie", mower1, zombie);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

	glViewport(0, 0, 800, 800);

	if (state == MAIN)
	{
		projection = glm::mat4(1.0f);

		/*projection = glm::perspective(glm::radians(45.0f),1.0f,0.1f,50.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));

		projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

		world.setting(glm::vec3(0.0f, 10.0f, 25.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 100.0, 0.0));*/

		projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);

		projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

		world.setting(glm::vec3(0.0f, 9.9f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0, 100.0, 0.0));
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
	for (auto& object : world.all_object())
	{
		object->Move();

		if (object == dynamic_cast<Zombie*>(object))
			object->Attack();
	}
}

void CScene::Update2()
{
	for (auto& object : world.all_object())
	{
		if (object == dynamic_cast<Plant*>(object))
			object->Attack();
	}

	for (auto group : world.all_collision_group())
	{
		cout << "string: " << group.first << endl;
		for (auto a : get<0>(group.second))
		{
			cout << "left: " << a << endl;
		}
		for (auto b : get<1>(group.second))
		{
			cout << "right: " << b << endl;
		}
	}

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
						cout << "Init_Lose()" << endl;
						Init_Lose();
						return;
					}
					a->Get_Collide(b, group.first);
					b->Get_Collide(a, group.first);
					return;
				}
			}
		}
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

bool CScene::collide(Model* a, Model* b)
{
	if (a == nullptr || b == nullptr) return false;
	if (a->Get_Max().x < b->Get_Min().x || a->Get_Min().x > b->Get_Max().x) return false;
	if (a->Get_Max().y < b->Get_Min().y || a->Get_Min().y > b->Get_Max().y) return false;
	if (a->Get_Max().z < b->Get_Min().z || a->Get_Min().z > b->Get_Max().z) return false;

	return true;
}