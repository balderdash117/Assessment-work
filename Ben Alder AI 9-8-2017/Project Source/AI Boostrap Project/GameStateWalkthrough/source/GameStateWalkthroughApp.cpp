#include "GameStateWalkthroughApp.h"
#include "Texture.h"
#include "Font.h"

#include "SpalshState.h"
#include "pauseSate.h"
#include "menuState.h"
#include "playState.h"
#include "chooseGameState.h"

#include "GameStateManager.h"

GameStateWalkthroughApp::GameStateWalkthroughApp() {

}

GameStateWalkthroughApp::~GameStateWalkthroughApp() {

}

bool GameStateWalkthroughApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font1 = new aie::Font("./font/Promocyja096.ttf", 128);
	m_font2 = new aie::Font("./font/Promocyja096.ttf", 64);
	background = new aie::Texture("./textures/gameBackground.png");
	playButton = new aie::Texture("./textures/i_playButton.png");
	optionsButton = new aie::Texture("./textures/i_optionsButton.png");
	exitButton = new aie::Texture("./textures/i_exitButton.png");

	m_GameStateManager = new GameStateManager();
	m_GameStateManager->setState("splash", new SplashState(this));
	m_GameStateManager->setState("menu", new menuState(this));
	m_GameStateManager->setState("chooseGame", new chooseGameState(this));
	m_GameStateManager->setState("pause", new pauseSate(this));
	m_GameStateManager->setState("play", new playState(this));

	m_GameStateManager->pushState("splash");

	return true;
}

void GameStateWalkthroughApp::shutdown() {
	delete m_GameStateManager;
	delete m_font1;
	delete m_font2;
	delete background;
	delete m_2dRenderer;
	delete playButton;
	delete optionsButton;
	delete exitButton;
}

void GameStateWalkthroughApp::update(float deltaTime)
{

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_GameStateManager->updateStates(deltaTime);
}


void GameStateWalkthroughApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_GameStateManager->drawGameStates();
	// output some text, uses the last used colour

	// done drawing sprites
	m_2dRenderer->end();
}

aie::Renderer2D * GameStateWalkthroughApp::GetRenderer()
{
	return m_2dRenderer;
}

GameStateManager * GameStateWalkthroughApp::getGameStateManager()
{
	return m_GameStateManager;
}

float GameStateWalkthroughApp::positionButtonX()
{
	buttonPosX = ((float)getWindowWidth() / 2);
	return buttonPosX;
}

float GameStateWalkthroughApp::positionButtonY(int buttonNum)
{
	switch (buttonNum)
	{
	case 1:
		buttonPosY = ((float)getWindowHeight() / 4) * 3 - 75;
		break;
	case 2:
		buttonPosY = ((float)getWindowHeight() / 4) * 2;
		break;
	case 3:
		buttonPosY = ((float)getWindowHeight() / 4) * 1 + 75;
		break;
	default:
		buttonPosY = 10;
		break;
	}

	return buttonPosY;
}

GameStateManager *GameStateWalkthroughApp::Get_GSM()
{
	return m_GameStateManager;
}