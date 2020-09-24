#pragma once
#include "PhysicsObject.h"

///
///Contains functions that have to do with rigid bodies.
///
class RigidBody : public PhysicsObject
{
public:
	///
	///Constructor for the RigidBody class.
	///
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	///
	///Deconstructor for the RigidBody class.
	///
	~RigidBody() {}

	///
	///Updates rigid bodies at a fixed rate.
	///
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);

	///
	///Applies a force to a rigid body.
	///
	void applyForce(glm::vec2 force, glm::vec2 position);

	///
	///Resolves what happens when rigid bodies collide.
	///
	void resolveCollision(RigidBody* other, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

	///
	///Returns the position of a rigid body.
	///
	glm::vec2 getPosition() { return m_position; }
	///
	///Returns the velocity of a rigid body.
	///
	glm::vec2 getVelocity() { return m_velocity; }
	///
	///Returns the rotation of a rigid body.
	///
	float getRotation() { return m_rotation; }
	///
	///Returns the mass of a rigid body.
	///
	float getMass() { return m_mass; }

	///
	///Returns the moment of a rigid body.
	///
	float getMoment() { return m_moment; }
	///
	///Sets the moment of a rigid body.
	///
	float setMoment(float value) { m_moment = value; }

	///
	///Returns the linear drag of a rigid body.
	///
	float getLinearDrag() { return m_linearDrag; }
	///
	///Sets the linear drag of a rigid body.
	///
	float setLinearDrag(float value) { m_linearDrag = value; }

	///
	///Returns the angular drag of a rigid body.
	///
	float getAngularDrag() { return m_angularDrag; }
	///
	///Sets the angular drag of a rigid body.
	///
	float setAngularDrag(float value) { m_angularDrag = value; }

	///
	///Returns the elasticity of a rigid body.
	///
	float getElasticity() { return m_elasticity; }
	///
	///Sets the elasticity of a rigid body.
	///
	float setElasticity(float value) { m_elasticity = value; }

protected:
	///
	///Holds the position of a rigid body.
	///
	glm::vec2 m_position;
	///
	///Holds the velocity of a rigid body.
	///
	glm::vec2 m_velocity;
	///
	///Holds the angular velocity of a rigid body.
	///
	float m_angularVelocity;
	///
	///Holds the rotation of a rigid body.
	///
	float m_rotation;
	///
	///Holds the mass of a rigid body.
	///
	float m_mass;
	///
	///Holds the moment of a rigid body.
	///
	float m_moment;
	///
	///Holds the linear drag of a rigid body.
	///
	float m_linearDrag = 0.3f;
	///
	///Holds the angular drag of a rigid body.
	///
	float m_angularDrag = 0.3f;
	///
	///Holds the elasticity of a rigid body.
	///
	float m_elasticity = 0.5f;
};

