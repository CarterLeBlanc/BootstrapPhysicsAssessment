#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

///
///Initializes the game and loops it.
///
class PhysicsDemoApp : public aie::Application {
public:

	///
	///Constructor for the PhysicsDemoApp class.
	///
	PhysicsDemoApp() {}
	///
	///Deconstructor for the PhysicsDemoApp class.
	///
	virtual ~PhysicsDemoApp() {}

	///
	///Initializes the scene and applies variables when the program runs.
	///
	virtual bool startup();
	///
	///Deletes objects displayed to the console when the program is ended.
	///
	virtual void shutdown();

	///
	///Updates objects in the scene every frame.
	///
	virtual void update(float deltaTime);
	///
	///Prints objects to the console.
	///
	virtual void draw();
	
	///
	///Creates a sphere and adds it to the scene.
	///
	void initializeBall();

	///
	///Calculates the velocity of objects.
	///
	glm::vec2 calculateVelocity(glm::vec2 initialPosition, glm::vec2 finalPosition, float gravity, float time);

protected:
	///
	///Holds a pointer of the renderer.
	///
	aie::Renderer2D*	m_2dRenderer;
	///
	///Holds a pointer of the font.
	///
	aie::Font*			m_font;
	///
	///Holds a pointer of the physics scene.
	///
	PhysicsScene* m_physicsScene;
};