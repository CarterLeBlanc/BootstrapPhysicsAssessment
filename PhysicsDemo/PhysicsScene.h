#pragma once
#include "PhysicsObject.h"
#include "glm\ext.hpp"
#include <vector>

///
///Contains functions for interations between objects with physics.
///
class PhysicsScene
{
public:
	///
	///Constructor for the PhysicsScene class.
	///
	PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0.0f, 0.0f)) {}
	///
	///Deconstructor for the PhysicsScene class.
	///
	~PhysicsScene();

	///
	///Adds an actor to the scene.
	///
	void addActor(PhysicsObject* actor);
	///
	///Removes an actor from the scene.
	///
	void removeActor(PhysicsObject* actor);
	///
	///Updates the scene after a specified amount of time.
	///
	void update(float deltaTime);
	///
	///Updates the gizmos used in the scene.
	///
	void updateGizmos();

	///
	///Sets the gravity in the scene.
	///
	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	///
	///Returns the gravity of an object.
	///
	glm::vec2 getGravity() const { return m_gravity; }

	///
	///Sets the timeStep.
	///
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	///
	///Returns the timeStep.
	///
	float getTimeStep() const { return m_timeStep; }

	///
	///Checks for collisions in the scene.
	///
	void checkForCollision();

	///
	///Resolves what happens when a plane collides with another plane.
	///
	static bool planeToPlane(PhysicsObject* object1, PhysicsObject* object2);
	///
	///Resolves what happens when a plane collides with a sphere.
	///
	static bool planeToSphere(PhysicsObject* object1, PhysicsObject* object2);
	///
	///Resolves what happens when a sphere collides with a plane.
	///
	static bool sphereToPlane(PhysicsObject* object1, PhysicsObject* object2);
	///
	///Resolves what happens when a sphere collides with another sphere.
	///
	static bool sphereToSphere(PhysicsObject* object1, PhysicsObject* object2);

protected:
	///
	///Holds the rate at which objects fall.
	///
	glm::vec2 m_gravity;
	///
	///Holds the timeStep.
	///
	float m_timeStep;
	///
	///Pointer for a list of actors.
	///
	std::vector<PhysicsObject*> m_actors;
};