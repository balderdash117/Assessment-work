#include "firstProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

firstProjectApp::firstProjectApp() {

}

firstProjectApp::~firstProjectApp() {

}

bool firstProjectApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_myImage = new aie::Texture("./textures/car.png");

	return true;
}

void firstProjectApp::shutdown() {
	delete m_myImage;
	delete m_font;
	delete m_2dRenderer;
}

void firstProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (input->isKeyDown(aie::INPUT_KEY_LEFT) || input->isKeyDown(aie::INPUT_KEY_A))
	{ 
		float xDir = -cos(m_rotation);
		float yDir = -sin(m_rotation);
		m_xPos += xDir;
		m_yPos += yDir;
		//m_rotation = 3.14159265359 / 2.0f;
	}

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT) || input->isKeyDown(aie::INPUT_KEY_D))
	{
		float xDir = cos(m_rotation);
		float yDir = sin(m_rotation);
		m_xPos += xDir;
		m_yPos += yDir;
		//m_rotation = 3.0 * 3.14159265359 / 2.0f;
	}

	if (input->isKeyDown(aie::INPUT_KEY_UP) || input->isKeyDown(aie::INPUT_KEY_W))
	{
		
		float xDir = -sin(m_rotation);
		float yDir = cos(m_rotation);
		m_xPos += xDir;
		m_yPos += yDir;
		//m_rotation = 0.0f;
	}

	if (input->isKeyDown(aie::INPUT_KEY_DOWN) || input->isKeyDown(aie::INPUT_KEY_S))
	{
		float xDir = sin(m_rotation);
		float yDir = -cos(m_rotation);
		m_xPos += xDir;
		m_yPos += yDir;
		//m_rotation = 3.14159265359f;
	}

	double scrollValue = input->getMouseScroll();
	double deltaScroll = (m_lastScrollValue - scrollValue) / 2;
	m_lastScrollValue = scrollValue;

	m_rotation += deltaScroll;
}

void firstProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_2dRenderer->drawSprite(m_myImage, m_xPos, m_yPos, 0.0f, 0.0f, m_rotation);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}