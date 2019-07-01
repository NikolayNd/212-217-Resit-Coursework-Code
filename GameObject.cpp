#include "GameObject.h"
#include "GameEngine.h"
#include <map>


std::map <int, bool> GameObject::specialKeys;
std::map <char, bool> GameObject::keys;
//Lambda functions to link our code to glut's keydown and keyup. Our function deals with both regular and special keys in one.

GameObject::GameObject(glm::vec3 position, Colour colour)
{	
	this->position = position;
}

GameObject::~GameObject()
{
}

unsigned int GameObject::setupDrawing(unsigned int listBase)
{
	return 0;
}

void GameObject::drawScene()
{
	glPushMatrix();
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glCallList(this->base);
	glPopMatrix();
	if (GameEngine::debugMode) {
		if (this->collider != NULL) {
			this->collider->Draw();
		}
	
	}
}

void GameObject::collides(Collider * other)
{
}
