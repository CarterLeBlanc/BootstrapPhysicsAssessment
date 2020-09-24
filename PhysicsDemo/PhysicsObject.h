#pragma once
#include "glm\ext.hpp"

///
///Enumerator that contains PLANE, SPHERE, and SHAPE_COUNT
///
enum ShapeType 
{
	PLANE = 0,
	SPHERE,
	SHAPE_COUNT
};

///
///Creates objects that have physics applied to them.
///
class PhysicsObject
{
protected:
	///
	///Constructor for the PhysicsObject class.
	///
	PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) {}

public:
	///
	///Updates the program at a fixed rate.
	///
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	///
	///Creates a gizmo when called.
	///
	virtual void makeGizmo() = 0;
	///
	///Resets the position of an object.
	///
	virtual void resetPosition() {};

	///
	///Returns the shape ID of an object.
	///
	ShapeType getShapeID() { return m_shapeID; }

protected:
	///
	///Holds the shape ID of an object.
	///
	ShapeType m_shapeID;
};