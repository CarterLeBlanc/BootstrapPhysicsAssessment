#pragma once
#include "Application.h"
#include "Renderer2D.h"

class PhysicsDemoApp : public aie::Application {
public:

	PhysicsDemoApp() {}
	virtual ~PhysicsDemoApp() {}

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	//void setupContinuousDemo(glm::vec2 initialPosition, glm::vec2 initialVelocity, )

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};