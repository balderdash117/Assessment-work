#pragma once

#include "Application.h"
#include "Renderer2D.h"

class firstProjectApp : public aie::Application {
public:

	firstProjectApp();
	virtual ~firstProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture*		m_myImage;

	float m_xPos = 100.0f;
	float m_yPos = 100.0f;
	float m_rotation = 0.0f;

	double m_lastScrollValue = 0.0f;
};