#include "scene.h"

CScene::CScene() {}
CScene::~CScene() {}


void CScene::Init_Begin()
{
	shader.InitShader();

	display = new Display();
	world.add_object(display);

	for (auto& object : world.all_object())
	{
		object->InitTexture();
	}

	projection = glm::mat4(1.0f);
	projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	world.setting(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 5.0, 10.0));
}

void CScene::Init_Select()
{

}

void CScene::Init_Main()
{
	plane = new Plane();
	cherry = new F_Modapi();
	zombie = new GoldZombie(1);

	shader.InitShader();
	world.add_object(plane);
	world.add_object(cherry);
	world.add_object(zombie);

	for (auto& object : world.all_object())
	{
		object->InitTexture();
	}

	projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f),1.0f,0.1f,50.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));

	projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	world.setting(glm::vec3(0.0f, 10.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 100.0, 0.0));

}

void CScene::Init_End()
{

}

void CScene::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, polymod);

	for (auto& object : world.all_object())
	{
		object->InitBuffer();
		object->Move_Update();
		object->Attack_Update();
		object->Render();
	}
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