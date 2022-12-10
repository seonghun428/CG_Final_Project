#include "scene.h"

Scene::Scene() {}
Scene::~Scene() {}


void Scene::Init_Begin()
{
	
}

void Scene::Init_Select()
{

}

void Scene::Init_Main()
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

void Scene::Init_End()
{

}

void Scene::Render()
{
	glUseProgram(shader.Get_ShaderID());

	for (auto& object : world.all_object())
	{
		object->InitBuffer();
		object->Render();
	}
}