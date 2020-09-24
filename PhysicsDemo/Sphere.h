#pragma once
#include "RigidBody.h"

///
///Contains functions that have to do with spheres.
///
class Sphere : public RigidBody
{
public:
	///
	///Constructor for the Sphere class.
	///
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color);
	///
	///Deconstructor for the Sphere class.
	///
	~Sphere() {}

	///
	///Creates a gizmo.
	///
	virtual void makeGizmo();

	///
	///Returns the radius of a sphere.
	///
	float getRadius() { return m_radius; }
	///
	///Returns the color of a sphere.
	///
	glm::vec4 getColor() { return m_color; }

protected:
	///
	///Holds the radius of a sphere.
	///
	float m_radius;
	///
	///Holds the color of a sphere.
	///
	glm::vec4 m_color;
};

