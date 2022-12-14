#include "plant.h"
#include "scene.h"

void Plant::InitBuffer()
{
	for (auto& element : elements)
	{
		element->InitBuffer();
		element->Update_Translate_Matrix(glm::vec3((x - 4) * 1.85 - 0.7, 0.0, (y - 3) * 1.9));
	}
}

void Plant::Get_Collide(Model* other, string group)
{
	if (hp > 0)
	{
		if (group == "plant:zombie")
		{
			if (other->Attacking())
				hp -= 1;
		}
		if (hp == 0)
		{
			extern CScene scene;
			scene.world.remove_object(this);
			return;
		}
	}
}