#include "Sphere.h"
#include <Gizmos.h>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color) :
	RigidBody(SPHERE, position, velocity, 0.0f, mass)
{
	m_radius = radius;
	m_color = color;
	m_moment = 0.5f * mass * radius * radius;
}

void Sphere::makeGizmo()
{
	//Draw circle
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_color);

	//Draw a line to show rotation
	glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) * m_radius;
	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}