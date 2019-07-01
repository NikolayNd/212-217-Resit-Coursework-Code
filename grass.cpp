#include "grass.h"
#include "HoverCraft.h"
#include "GameEngine.h"
#include "CubeCollider.h"
#include"getbmp.h"

grass::grass(glm::vec3 position, Colour colour) : GameObject(position)
{
	this->colour = colour;
	grass::collider = new CubeCollider(&this->position, 300, 400, 3);
	grass::collider->name = "grass";
}

grass::~grass()
{
	delete grass::collider;
	grass::collider = NULL;
}



unsigned int  grass::setupDrawing(unsigned int listBase) {
	this->base = ++listBase;

	glNewList(this->base, GL_COMPILE);

	glPushMatrix();

	glColor3f(this->colour.r, this->colour.g, this->colour.b);

	glBegin(GL_QUADS);

	glVertex3f(150, 200, 0);

	glVertex3f(-150, 200, 0);

	glVertex3f(-150, -200, 0);

	glVertex3f(150, -200, 0);

	glEnd();

	glPopMatrix();

	glEndList();

	return this->base;
}

void grass::start()
{
	
}

void grass::update(int deltaTime)
{
}

void grass::collides(Collider* other) {
	if (GameEngine::debugMode) {
		//std::cout << "grass collides" << std::endl;
	}
}


