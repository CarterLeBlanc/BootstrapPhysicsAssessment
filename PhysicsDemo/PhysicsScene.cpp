#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include <list>

PhysicsScene::~PhysicsScene()
{
	for (auto actor : m_actors)
	{
		delete actor;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	for (auto i = m_actors.begin(); i < m_actors.end(); i++)
	{
		if (*i == actor)
		{
			m_actors.erase(i);
		}
	}
}

void PhysicsScene::update(float deltaTime)
{
	//Store how much time has accumulated since last update
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	//While enough time has accumulated...
	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			//Update the physics of that object
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		//Spend the time needed for that update
		accumulatedTime -= m_timeStep;

		//Check for collisions
		checkForCollision();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	for (auto actor : m_actors)
	{
		actor->debug();
	}
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctions[] =
{
	PhysicsScene::planeToPlane, PhysicsScene::planeToSPhere,
	PhysicsScene::sphereToPlane, PhysicsScene::sphereToSphere
};

void PhysicsScene::checkForCollision()
{
	//Get the number of actors in the scene
	int actorCount = m_actors.size();

	//Check for collisions against all objects except this one
	for (int y = 0; y < actorCount - 1; y++)
	{
		for (int x = y + 1; x < actorCount; x++)
		{
			PhysicsObject* object1 = m_actors[y];
			PhysicsObject* object2 = m_actors[x];
			int shapeID1 = object1->getShapeID();
			int shapeID2 = object2->getShapeID();

			//Find the function's position in the collision function array
			int functionID = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFunctionPtr = collisionFunctions[functionID];

			if (collisionFunctionPtr != nullptr)
			{
				//Check collision
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::planeToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	Plane* plane1 = dynamic_cast<Plane*>(object1);
	Plane* plane2 = dynamic_cast<Plane*>(object2);

	if (plane1 != nullptr && plane2 != nullptr)
	{
		if (plane1->getNormal().x != plane2->getNormal().x || plane1->getNormal().y != plane2->getNormal().y)
		{
			return true;
		}
	}

	return false;
}

bool PhysicsScene::planeToSPhere(PhysicsObject* object1, PhysicsObject* object2)
{
	sphereToPlane(object2, object1);
	return false;
}

bool PhysicsScene::sphereToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(object1);
	Plane* plane = dynamic_cast<Plane*>(object2);

	if (sphere != nullptr && plane != nullptr)
	{
		//Calculate the distance from sphere surface to plane surface
		float sphereToPlaneDistance = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

		//Flip the normal if behind the plane
		glm::vec2 collisionNormal = plane->getNormal();

		if (sphereToPlaneDistance < 0.0f)
		{
			collisionNormal *= -1.0f;
			sphereToPlaneDistance *= -1.0f;
		}

		sphereToPlaneDistance -= sphere->getRadius();

		if (sphereToPlaneDistance <= 0)
		{
			//Resolve collision
			glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());
			plane->resolveCollision(sphere, contact);
			return true;
		}
	}

	return false;
}

bool PhysicsScene::sphereToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) < sphere1->getRadius() + sphere2->getRadius())
		{
			//Resolve collision
			glm::vec2 contact = (sphere1->getPosition() + sphere2->getPosition()) * 0.5f;
			glm::vec2 contactButStrnger = glm::vec2(0, 0);
			glm::vec2* b = &contactButStrnger;
			sphere1->resolveCollision(sphere2, contact, b);
			return true;
		}
	}

	return false;
}