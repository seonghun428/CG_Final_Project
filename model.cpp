#include "model.h"
#include "scene.h"

void Model::InitBuffer()
{
	for (auto& element : elements)
	{
		element->InitBuffer();
	}
}

void Model::InitTexture()
{
	for (auto& element : elements)
	{
		element->InitTexture();
	}
}

void Model::Render()
{
	for (auto& element : elements)
	{
		element->Render();
	}
}