#include "Plane.h"
#include <Gizmos.h>

Plane::Plane() : PhysicsObject(PLANE)
{
	//Set the variables
	m_normal = glm::vec2(0.0f, 1.0f);
	m_distanceToOrigin = 0.0f;
}

Plane::Plane(glm::vec2 normal, float distanceToOrigin) : PhysicsObject(PLANE)
{
	//Set the variables
	m_normal = normal;
	m_distanceToOrigin = distanceToOrigin;
}

void Plane::makeGizmo()
{
	//Create a visual for the plane
	float lineSegmentLength = 300.0f;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, color);
}

void Plane::resolveCollision(RigidBody* other, glm::vec2 contact)
{
	//Apply force to the objects involved in a collision
	glm::vec2 collisionNormal = m_normal;
	glm::vec2 relativeVelocity = other->getVelocity();

	float elasticity = 1.0f;
	float j = glm::dot(-(1.0f + elasticity) * (relativeVelocity), collisionNormal) / (1.0f / other->getMass());

	glm::vec2 force = collisionNormal * j;
	other->applyForce(force, contact - other->getPosition());
}