#pragma once

#include "GameObject.h"

struct Colour {
	float r, g, b;
};

class Obstacle : public GameObject
{
private:
	Colour colour;
public:
	Obstacle(glm::vec3 pos, GameObject::Colour colour = { 1.0f, 0.1f,0.1f });
	~Obstacle();
	void collides(Collider* other);
	unsigned int setupDrawing(unsigned int listBase);
	void start();
	void update(int deltaTime);
};
