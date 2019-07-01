#pragma once
#include "GameObject.h"

#include<glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>

#define TURNING_SPEED 90.0 //<turning speed in degrees per second
#define MOVE_SPEED 50.0 //<move speed in coordinate units per second

class HoverCraft : public GameObject
{

public:
	glm::vec3 startingHeading = heading; ///<Starting facing direction of the Hovercraft.
	float rotationAngle = 0.0f;
	glm::vec3 velocity = glm::vec3(0,0,0);
	float acc = 0.0f;
	float mass = 3;
	std::string name;
	float pitchAngle = 0.0f; ///<Rotation and pitch angles for our Hovercraft
	void collides(Collider* other);
	HoverCraft(glm::vec3 pos, GameObject::Colour colour = { 1, 1, 1 });
	~HoverCraft();
	unsigned int setupDrawing(unsigned int listBase);
	void start();
	void update(int deltaTime);
	void drawScene();
};