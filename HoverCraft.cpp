#include "HoverCraft.h"
#include "CubeCollider.h"
#include "GameEngine.h"
#include <iostream>
#include "reader.h"

HoverCraft::HoverCraft(glm::vec3 position, Colour colour): GameObject(position)
{
	this->colour = colour;
	HoverCraft::collider = new CubeCollider(&this->position, 2, 2, 1.5);
	HoverCraft::collider->name = "Cue";
}

HoverCraft::~HoverCraft()
{
	delete HoverCraft::collider;
	HoverCraft::collider = NULL;
}
unsigned int  HoverCraft::setupDrawing(unsigned int listBase) {
	

	this->base = ++listBase;
	glNewList(this->base, GL_COMPILE);
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glRotatef(-45, 1, 0, 0);
	glutSolidSphere(3, 20, 20);
	glPopMatrix();
	glEndList();
	return this->base;
}

void HoverCraft::drawScene()
{
	glPushMatrix();
		glTranslatef(this->position.x, this->position.y, this->position.z);
		//rotate openGL object
		glRotatef(pitchAngle, 0.0, 0.0, 1.0);
		glRotatef(rotationAngle, 0.0, 0.0, -1.0);

		glCallList(this->base); // Draw Hovercraft.
	glPopMatrix(); 
	if (GameEngine::debugMode) {
		HoverCraft::collider->Draw();
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex3f(position.x, position.y, position.z);
		glVertex3f(position.x + heading.x * 10, position.y + heading.y * 10, position.z + heading.z * 10);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex3f(position.x + 3, position.y, position.z);
		glVertex3f(position.x + 9, position.y, position.z);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex3f(position.x, position.y + 3, position.z);
		glVertex3f(position.x, position.y + 9, position.z);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex3f(position.x, position.y, position.z + 3);
		glVertex3f(position.x, position.y, position.z + 9);
		glEnd();
	}
}  

void HoverCraft::start()
{
}

void HoverCraft::update(int deltaTime)
{
	float turningSpeed = TURNING_SPEED * (deltaTime / 1000.0); //turning speed (degrees/sec) * deltaTime in sec = turning speed over delta time
	//newVel = glm::clamp(newVel, -3.0f, 3.0f);
	//std::cout << acc << std::endl;
	//std::cout << glm::to_string(newVel) << std::endl;


	glm::vec3 newVel = this->velocity + ((this->acc * this->heading) * (deltaTime/ 1000.0f));
	glm::vec3 newPos = this->position + newVel * (deltaTime / 1000.0f);
	this->position = newPos;

	if (specialKeys[GLUT_KEY_UP]) {
		if (acc > 10000) {
			acc = 10000;
		}
		else {
			this->acc += 10.0f / mass;
		}
	}
	else if (specialKeys[GLUT_KEY_DOWN]) {		
		if (acc < -5000) {
			acc = -5000;
		}
		else {
			this->acc -= 10.0f / mass;
		}
	}
	else
	{
		if (this->acc > 0.0f)
			this->acc -= 5.0f;
		if (this->acc < 0.0f)
			this->acc += 5.0f;
		if (this->acc <= 5.0f && this->acc >= -5.0f)
			this->acc = 0.0f;
	}

	if (specialKeys[GLUT_KEY_LEFT]) {
		this->pitchAngle -= turningSpeed; //in degrees not radians
	}
	if (specialKeys[GLUT_KEY_RIGHT]) {
		this->pitchAngle += turningSpeed; //in degrees not radians
	}
	//rotate the heading
	//In the drawscene we will need to rotate by the full rotation since the start
	//Therfore we start heard from the original startingheading, so that we can use the same variables for the rotations

	//update velocity 

	this->heading = glm::rotate(this->startingHeading, glm::radians(rotationAngle), glm::vec3(0.0, 1.0, 0.0));
	this->heading = glm::rotate(this->heading, glm::radians(pitchAngle), glm::vec3(0.0, 0.0, 1.0));

}
void HoverCraft::collides(Collider* other) {
	if (GameEngine::debugMode) {
		std::cout << "Cue ball collides!" << std::endl;
		
	}
}
