#pragma once
#include "GameObject.h"

class Track : public GameObject
{
public:
	Track(glm::vec3 position, GameObject::Colour colour = { 39.6f, 26.3f, 12.9f });
	~Track();
	unsigned int setupDrawing(unsigned int listBase);
	void start();
	void update(int deltaTime);
};
