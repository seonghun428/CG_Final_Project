#include "plant.h"

void Plant::InitBuffer()
{
	for (auto& element : elements)
	{
		element->InitBuffer();
		element->Update_Translate_Matrix(glm::vec3((x - 4) * 1.85 - 0.7, 0.0, (y - 3) * 1.9));
	}
}