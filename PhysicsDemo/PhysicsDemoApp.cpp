#include "PhysicsDemoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Sphere.h"
#include "Plane.h"
#include <Gizmos.h>

bool PhysicsDemoApp::startup()
{
	//Increase the 2D line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	//Initialize gravity
	glm::vec2 gravity = glm::vec2(0.0f, -80.0f);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(gravity);
	m_physicsScene->setTimeStep(0.01f);

	//Initialize position and velocity
	glm::vec2 initialPosition = glm::vec2(-60.0f, 0.0f);
	glm::vec2 finalPosition = glm::vec2(60.0f, 0.0f);
	glm::vec2 initialVelocity = calculateVelocity(initialPosition, finalPosition, gravity.y, 5.0f);


	//Create objects and print them to the screen
	Plane* floor = new Plane(glm::vec2(0.0f, 1.0f), -50.0f);
	m_physicsScene->addActor(floor);

	Plane* roof = new Plane(glm::vec2(0.0f, 1.0f), 50.0f);
	m_physicsScene->addActor(roof);

	Plane* leftWall = new Plane(glm::vec2(1.0f, 0.0f), -80.0f);
	m_physicsScene->addActor(leftWall);

	Plane* rightWall = new Plane(glm::vec2(1.0f, 0.0f), 80.0f);
	m_physicsScene->addActor(rightWall);

	return true;
}

void PhysicsDemoApp::shutdown() 
{

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsDemoApp::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	//Clear the buffer
	aie::Gizmos::clear();

	//Update the scene
	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	if (input->wasMouseButtonPressed(0)) 
	{
		initializeBall();
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsDemoApp::draw() 
{

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100.0f, 100.0f, -100.0f / aspectRatio, 100.0f / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsDemoApp::initializeBall()
{
	glm::vec2 gravity = glm::vec2(0.0f, -80.0f);
	glm::vec2 initialPosition = glm::vec2(-60.0f, 0.0f);
	glm::vec2 finalPosition = glm::vec2(60.0f, 0.0f);
	glm::vec2 initialVelocity = calculateVelocity(initialPosition, finalPosition, gravity.y, 5.0f);

	Sphere* ball = new Sphere(initialPosition, initialVelocity, 10.0f, 5.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	m_physicsScene->addActor(ball);
}

glm::vec2 PhysicsDemoApp::calculateVelocity(glm::vec2 initialPosition, glm::vec2 finalPosition, float gravity, float time)
{
	glm::vec2 initialVelocity = glm::vec2(0.0f, 0.0f);

	initialVelocity.x = (finalPosition.x - initialPosition.x) / time;
	initialVelocity.y = (finalPosition.y - initialPosition.y - (0.5f * gravity * (time * time)) / time);

	return initialVelocity;
}