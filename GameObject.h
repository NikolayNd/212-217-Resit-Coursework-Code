#pragma once
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif

#include "Collider.h"
# include <iostream>
# include <glm/glm.hpp> 
# include <map>


class GameObject
{
protected:
	struct Colour {
		float r, g, b;
	};
	Colour colour;
	unsigned int base;
public:
	static std::map <int, bool> specialKeys;
	static std::map <char, bool> keys;
	Collider* collider = NULL;
	bool active = true;
	glm::vec3 heading = glm::vec3(-1.0, 0.0, 0.0);  ///<Current heading (direction) the GameObject is facing.
	glm::vec3 position;
	GameObject(glm::vec3 position, Colour colour = { 0.1f, 0.1f, 0.1f });
	~GameObject();
	virtual unsigned int setupDrawing(unsigned int listBase);
	virtual void drawScene();
	/* Every GameObject must implement the following pure virtual function or otherwise cause a compile error.*/
	virtual void start() = 0; ///<Pure virtual start function, run once when the engine starts.  Must override in inherited classes.
	virtual void update(int deltaTime) = 0; ///<Pure virtual update function, run periodicly to update the game state. Must override in inherited classes.
	virtual void collides(Collider* other);
};