#include "scene.h"

CScene::CScene() {}
CScene::~CScene() {}


void CScene::Init_Begin()
{
	
}

void CScene::Init_Select()
{

}

void CScene::Init_Main()
{
	plane = new Plane();
	cherry = new Cherry();
	zombie = new GoldZombie(2);

	shader.InitShader();
	world.add_object(plane);
	world.add_object(cherry);
	world.add_object(zombie);

	for (auto& object : world.all_object())
	{
		object->InitTexture();
	}

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

	unsigned int projectionLocation = glGetUniformLocation(shader.Get_ShaderID(), "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	world.setting(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 100.0, 0.0));

}

void CScene::Init_End()
{

}

void CScene::Render()
{
	glUseProgram(shader.Get_ShaderID());

	glPolygonMode(GL_FRONT_AND_BACK, polymod);

	for (auto& object : world.all_object())
	{
		object->InitBuffer();
		object->Render();
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