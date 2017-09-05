#include "AI_ProjectApp.h"
#include <Texture.h>
#include <Font.h>
#include <Input.h> 

#include "GameObject.h"
#include "keyboardBehaviour.h"
#include "graph2DRenderer.h"
#include "player.h"
#include "Townspeople.h"
#include "knights.h"

#include "GameStateManager.h"
#include "SpalshState.h"
#include "pauseSate.h"
#include "menuState.h"
#include "playState.h"
#include "controlsScreen.h"

#include "overlayClass.h"

#include "glm\glm.hpp"

AI_ProjectApp::AI_ProjectApp() 
{

}

AI_ProjectApp::~AI_ProjectApp() 
{
}

bool AI_ProjectApp::startup() 
{
	m_2dRenderer = new aie::Renderer2D();
	m_stateManager = new GameStateManager(this);
	m_stateManager->setState("splash", new SplashState(this));

	m_font1 = new aie::Font("./font/Promocyja096.ttf", 128);
	m_font2 = new aie::Font("./font/Promocyja096.ttf", 64);
	background = new aie::Texture("./textures/gameBackground.png");
	pauseText = new aie::Texture("./textures/pausedText.png");

	m_stateManager->setState("menu", new menuState(this));
	m_stateManager->setState("pause", new pauseSate(this));
	m_stateManager->setState("controls", new controlsScreen(this));
	m_stateManager->setState("play", new playState(this));
	
	m_stateManager->pushState("splash");

	playButton = new aie::Texture("./textures/i_playButton.png");
	optionsButton = new aie::Texture("./textures/i_optionsButton.png");
	exitButton = new aie::Texture("./textures/i_exitButton.png");

	m_showingGraph = false;

	return true;
}

void AI_ProjectApp::shutdown() 
{
	delete m_stateManager;
	delete m_2dRenderer;
	
	delete m_font1;
	delete m_font2;
	delete background;
	delete playButton;
	delete optionsButton;
	delete exitButton;
}

void AI_ProjectApp::update(float deltaTime) 
{
	m_windowWidth	= (float)getWindowWidth();
	m_windowHeight	= (float)getWindowHeight();

	// input example
	aie::Input* input = aie::Input::getInstance();

	int mx, my;
	input->getMouseXY(&mx, &my);
	m_mousePos = glm::vec2(mx, my);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	overlayClass::update();
	m_stateManager->updateStates(deltaTime);
}

void AI_ProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_stateManager->drawGameStates(m_2dRenderer);

	// done drawing sprites
	m_2dRenderer->end();
}

float AI_ProjectApp::positionButtonX()
{
	m_buttonPosX = ((float)getWindowWidth() / 2);
	return m_buttonPosX;
}

float AI_ProjectApp::positionButtonY(int buttonNum)
{
	switch (buttonNum)
	{
	case 1:
		m_buttonPosY = ((float)getWindowHeight() / 4) * 3 - 175;
		break;
	case 2:
		m_buttonPosY = ((float)getWindowHeight() / 4) * 2;
		break;
	case 3:
		m_buttonPosY = ((float)getWindowHeight() / 4) * 1 + 175;
		break;
	default:
		m_buttonPosY = 10;
		break;
	}

	return m_buttonPosY;
}

float AI_ProjectApp::returnWindowWidth()
{
	return m_windowWidth;
}

float AI_ProjectApp::returnWindowHeight()
{
	return m_windowHeight;
}

