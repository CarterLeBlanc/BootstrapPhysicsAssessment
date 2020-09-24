#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"

///
///Contains functions that have to do with planes.
///
class Plane : public PhysicsObject
{
public:
	///
	///Default constructor for the Plane class.
	///
	Plane();
	///
	///Modified constructor for the Plane class.
	///
	Plane(glm::vec2 normal, float distanceToOrigin);
	///
	///Deconstructor for the Plane class.
	///
	~Plane() {}

	///
	///Updates planes at a fixed rate.
	///
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) {}
	///
	///Creates a gizmo.
	///
	virtual void makeGizmo();
	///
	///Resolves what happens when something collides with a plane.
	///
	void resolveCollision(RigidBody* other, glm::vec2 contact);

	///
	///Returns the normal.
	///
	glm::vec2 getNormal() { return m_normal; }
	///
	///Returns the distance to the origin.
	///
	float getDistance() { return m_distanceToOrigin; }

protected:
	///
	///Holds the value of the normal.
	///
	glm::vec2 m_normal;
	///
	///Holds the distance to the origin.
	///
	float m_distanceToOrigin;
};

