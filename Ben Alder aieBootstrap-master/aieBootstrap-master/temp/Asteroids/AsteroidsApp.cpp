#include "AsteroidsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

AsteroidsApp::AsteroidsApp() {
	mAst.clear();
	mGameIsOver = false;
	mTimeInterval = 3.0f; // 3 Seconds between comets
	mScore = 0;
	mPlayer.mX = 0.f;
	mPlayer.mY = 0.f;
	mPlayer.mRadius = 25.f;
	mPlayer.mSpeed = 100.f;
	mBall.mX = mBall.mY = -1.f; //not in play
	mBall.mRadius = 10.0f;

}

bool AsteroidsApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	//Sprites will be ALL loaded here 


	mPlayer.mX = (float)getWindowWidth() / 2;
	mPlayer.mY = (float)getWindowHeight() / 2;

	//Setup Ball
	placeBallInPlay();
	mTimer = 0.f;
	return true;
}

//on shutdown will be accessed once 
void AsteroidsApp::shutdown() {
	//delete m_texture;
	//delete m_playterTexture;
	delete m_font;
	delete m_2dRenderer;
}

void AsteroidsApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void AsteroidsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void AsteroidsApp::sortAsteroids()
{
}

void AsteroidsApp::testCreateAsteroid(float deltaTime)
{
}

void AsteroidsApp::asteroidUpdate(Comet * a_ast, float deltaTime)
{
}
// if the ball is not in play place it in play
void AsteroidsApp::placeBallInPlay()
{
}

float AsteroidsApp::distance(float x1, float y1, float x2, float y2)
{
	return 0.0f;
}
