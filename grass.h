#pragma once
#include <iostream>
#include "getbmp.h"
#include "reader.h"
#include "GameObject.h"

class grass : public GameObject
{
private:
	
public:
	
	grass(glm::vec3 pos, GameObject::Colour colour = { 0.0f, 1.0f, 0.0f });
	~grass();
	void collides(Collider* other);
	unsigned int texture[1];
	BitMapFile*image[1];

	unsigned int setupDrawing(unsigned int listBase);
	void start();
	void update(int deltaTime);
};
