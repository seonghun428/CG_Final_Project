#include "penetrate_modapi.h"

P_Modapi::P_Modapi()
{
	hair = new Object("3DObjects/leaf_3.obj", "Textures/penetrate_leaf.png");
	head = new Object("3DObjects/modapi.obj", "Textures/penetrate_modapi.png");
	stem = new Object("3DObjects/stem.obj", "Textures/penetrate_stem.png");
	elements.push_back(hair);
	elements.push_back(head);
	elements.push_back(stem);
}