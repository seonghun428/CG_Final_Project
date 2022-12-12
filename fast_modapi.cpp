#include "fast_modapi.h"

F_Modapi::F_Modapi()
{
	hair = new Object("3DObjects/leaf_2.obj", "Textures/leaf.png");
	head = new Object("3DObjects/modapi.obj", "Textures/fast_modapi.png");
	stem = new Object("3DObjects/stem.obj", "Textures/stem.png");
	elements.push_back(hair);
	elements.push_back(head);
	elements.push_back(stem);
}