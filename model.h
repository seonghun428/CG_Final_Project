#pragma once

#include "header.h"
#include "object.h"

class Model
{
protected:
	vector<Object*> elements;

public:
	Model() {}
	virtual ~Model() { cout << "sibl" << endl; }

	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void Move_Update() = 0;
	virtual void Attack_Update() = 0;

	virtual void Get_Collide(Model* other, string group) = 0;

	virtual void InitBuffer();
	void InitTexture();
	void Render();

	virtual glm::vec3 Get_Max() = 0;
	virtual glm::vec3 Get_Min() = 0;
};