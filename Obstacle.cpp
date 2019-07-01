#include "Obstacle.h"
#include "HoverCraft.h"
#include "GameEngine.h"
#include "CubeCollider.h"

Obstacle::Obstacle(glm::vec3 position, Colour colour) : GameObject(position)
{
	this->colour = colour;
	Obstacle::collider = new CubeCollider(&this->position, 1.5, 1.5, 1.5);
	Obstacle::collider->name = "Obstacal";
}

Obstacle::~Obstacle() {
	delete Obstacle::collider;
	Obstacle::collider = NULL;
}

unsigned int  Obstacle::setupDrawing(unsigned int listBase) {
	this->base = ++listBase;
	glNewList(this->base, GL_COMPILE);
	glPushMatrix();
	glColor3f(this->colour.r, this->colour.g, this->colour.b);
	glRotatef(-45, 1, 0, 0);
	glutSolidSphere(3, 20, 20);
	glPopMatrix();
	glEndList();
	return this->base;
}

void Obstacle::start()
{
}

void Obstacle::update(int deltaTime)
{
}

void Obstacle::collides(Collider* other) {
	if (GameEngine::debugMode) {
		std::cout << "Obstacle collides, Obstacle will be removed!" << std::endl;
	}
	
	this->active = false;                 //Dissables(Deletes) the obstacle when it collides 
	
}