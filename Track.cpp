#include "Track.h"

#include "GameObject.h"
#include "reader.h"



Track::Track(glm::vec3 position, Colour colour) : GameObject(position)
{
	this->colour = colour;
}

Track::~Track()
{
}

unsigned int  Track::setupDrawing(unsigned int listBase) {
	int id;
	Reader obj;
	char filename[] = "MyPoolTable2.obj";
	obj.LoadModel(filename);

	this->base = ++listBase;
	glNewList(this->base, GL_COMPILE);

	// Modeling transformations.
	glTranslatef(0.0, 0.0, -9.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(15.0, 15.0, 15.0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.3f, 0.2f);
	for (int i = 0; i < obj.numPts; i++)
	{
		id = obj.faces[i].id1;
		glNormal3f(obj.normal[id].x, obj.normal[id].y, obj.normal[id].z);
		glVertex3d(obj.vertex[id].x, obj.vertex[id].y, obj.vertex[id].z);
		id = obj.faces[i].id2;
		glNormal3f(obj.normal[id].x, obj.normal[id].y, obj.normal[id].z);
		glVertex3d(obj.vertex[id].x, obj.vertex[id].y, obj.vertex[id].z);
		id = obj.faces[i].id3;
		glNormal3f(obj.normal[id].x, obj.normal[id].y, obj.normal[id].z);
		glVertex3d(obj.vertex[id].x, obj.vertex[id].y, obj.vertex[id].z);
		
		
	}
	glEnd();
	glPopMatrix();

	glEndList();
	return this->base;
}

void Track::start()
{



}

void Track::update(int deltaTime)
{
}