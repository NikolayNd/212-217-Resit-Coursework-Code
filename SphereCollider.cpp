#include "SphereCollider.h"
#include <iostream>
#include "glm/gtx/string_cast.hpp"
SphereCollider::SphereCollider(glm::vec3 centre, float radius, float materialBounce)
{
	this->colliderCentre = centre;	this->radius = radius;
	this->materialBounce = materialBounce;
}


SphereCollider::~SphereCollider()
{
}

//Collision between sphere and box
bool SphereCollider::collidesWithCube(CubeCollider * other)
{
	glm::vec3 corner;
	float cornerDistance;

	if (other == NULL) {
		return false;
	}

	//Calculating distance from sphere's centre to cube's centre
	glm::vec3 distance = this->colliderCentre - other->GetCenter();

	if (distance.x >= (other->width + this->radius) || distance.y >= (other->height + this->radius) || distance.z >= (other->length + this->radius)) //If distance < cube side + sphere radius, objects are not colliding
		return false;
	if (distance.x < other->width || distance.y < other->height || distance.z < other->length) //If distance < any of the cube's sides, we have a collision (sphere clipping in the cube)
		return true;

	corner = glm::vec3(distance.x - other->width, distance.y - other->height, distance.z - other->length); //Calculating the position of the closest cube corner to the sphere
	cornerDistance = glm::length(corner); //Magnitude of the corner

	return cornerDistance < this->radius * this->radius;

}

//Sphere-sphere collision
bool SphereCollider::collidesWithSphere(SphereCollider * other)
{
	glm::vec3 distance = this->colliderCentre - other->colliderCentre; //Distance between the two spheres
	float length = glm::length(distance);// distance.x * distance.x + distance.y * distance.y + distance.z * distance.z; //Length of the distance vector
	float sumRadii = this->radius + other->radius; //Sum of radii of the two spheres
	return length <= sumRadii;
}

float SphereCollider::minX()
{
	return this->colliderCentre.x - this->radius;
}

float SphereCollider::maxX()
{
	return this->colliderCentre.x + this->radius;
}

float SphereCollider::minY()
{
	return this->colliderCentre.y - this->radius;
}

float SphereCollider::maxY()
{
	return this->colliderCentre.y + this->radius;
}

float SphereCollider::minZ()
{
	return this->colliderCentre.z - this->radius;
}

float SphereCollider::maxZ()
{
	return this->colliderCentre.z + this->radius;
}