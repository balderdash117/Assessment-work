#include "AsteroidsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <windows.h>
//#include <math.h>
// Changes
//    1. Sprites added
//         a) Player, treasure and asteriods
//		   b) Background
//    2. Music added
//    3. Unique movement routine with scroll controlling rotation


AsteroidsApp::AsteroidsApp() {
	mAst.clear();
	mGameIsOver = false;
	mTimeInterval = 3.0f; // 3 Seconds between comets
	mScore = 0;
	mPlayer.mX = 0.f;
	mPlayer.mY = 0.f;
	mPlayer.mRadius = 37.f;
	mPlayer.mSpeed = 200.f;
	mBall.mX = mBall.mY = -1.f; //not in play
	mBall.mRadius = 10.0f;

}

bool AsteroidsApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_myImage = new aie::Texture("./textures/fighter-01.png");
	m_asteroid = new aie::Texture("./textures/rock_medium.png");
	m_backing = new aie::Texture("./textures/uniBack.jpg");
	m_chest = new aie::Texture("./textures/chest.png");
	m_halo = new aie::Audio("./audio/haloTheme.wav");
	m_beep = new aie::Audio("./audio/beep.wav");
	m_gameOver = new aie::Audio("./audio/gameOver.wav");
	m_controls = new aie::Texture("./textures/controlBoard.png");
	m_destroy = new aie::Audio("./audio/destroy.wav");
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
	delete m_myImage;
	delete m_asteroid;
	delete m_backing;
	delete m_chest;
	delete m_halo;
	delete m_beep;
	delete m_gameOver;
	delete m_controls;
	delete m_destroy;
}


void AsteroidsApp::update(float deltaTime) {

	static bool playOnce = false;
	static bool playsecond = false;

	if (!mGameIsOver)
	{
		m_halo->play();
		m_halo->setLooping(true);
		m_halo->setGain(0.2f);
	}
	else if (!playOnce)
	{
		if (!playsecond)
		{
			m_destroy->play();
			playOnce = true;
		}

		m_halo->stop();
		
		Sleep(1000);

		m_gameOver->play();
		playOnce = true;
	}
	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (mGameIsOver)return;

	mTimer += deltaTime;

	if (mBall.mX == -1)
	{
		placeBallInPlay();
	}

	testCreateAsteroid(deltaTime);

	sortAsteroids();

	for (unsigned int i = 0; i < mAst.size(); ++i)
	{
		asteroidUpdate(&mAst[i], deltaTime);
	}
	for (unsigned int i = mAst.size(); i--;)
	{
		if (mAst[i].mAsteroidActive) continue;
		mAst.erase(mAst.begin() + i);
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT) || input->isKeyDown(aie::INPUT_KEY_A))
	{
		float xDir = (float) -cos(m_rotation);
		float yDir = (float) -sin(m_rotation);
		mPlayer.mX = mPlayer.mX + xDir * mPlayer.mSpeed * deltaTime;
		mPlayer.mY = mPlayer.mY + yDir * mPlayer.mSpeed * deltaTime;

}

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT) || input->isKeyDown(aie::INPUT_KEY_D))
	{
		float xDir = (float) cos(m_rotation);
		float yDir = (float) sin(m_rotation);
		mPlayer.mX = mPlayer.mX + xDir * mPlayer.mSpeed * deltaTime;
		mPlayer.mY = mPlayer.mY + yDir * mPlayer.mSpeed * deltaTime;
	}

	if (input->isKeyDown(aie::INPUT_KEY_UP) || input->isKeyDown(aie::INPUT_KEY_W))
	{

		float xDir = (float) -sin(m_rotation);
		float yDir = (float) cos(m_rotation);
		mPlayer.mX = mPlayer.mX + xDir * mPlayer.mSpeed * deltaTime;
		mPlayer.mY = mPlayer.mY + yDir * mPlayer.mSpeed * deltaTime;
	}

	//if (input->isKeyDown(aie::INPUT_KEY_DOWN) || input->isKeyDown(aie::INPUT_KEY_S))
	//{
	//	float xDir = (float) sin(m_rotation);
	//	float yDir = (float) -cos(m_rotation);
	//	mPlayer.mX = mPlayer.mX + xDir * mPlayer.mSpeed * deltaTime;
	//	mPlayer.mY = mPlayer.mY + yDir * mPlayer.mSpeed * deltaTime;
	//}

	float scrollValue = (float)input->getMouseScroll();
	float deltaScroll = (float)(m_lastScrollValue - scrollValue) / 2;
	m_lastScrollValue = scrollValue;

	m_rotation += deltaScroll;

//this is borrowed code from Jack B
	// screen box (stops you from going past the sides)

	//if (mPlayer.mX - mPlayer.mRadius <= 0)
	//	mPlayer.mX = mPlayer.mRadius;

	//if (mPlayer.mX + mPlayer.mRadius >= getWindowWidth())
	//	mPlayer.mX = getWindowWidth() - mPlayer.mRadius;

	//if (mPlayer.mY - mPlayer.mRadius <= 0)
	//	mPlayer.mY = mPlayer.mRadius;

	//if (mPlayer.mY + mPlayer.mRadius >= getWindowHeight())
	//	mPlayer.mY = getWindowHeight() - mPlayer.mRadius;


	// screen wrap (lets you go through the sides of the screen)

	if (mPlayer.mX - mPlayer.mRadius <= 0) // left of screen
		mPlayer.mX = getWindowWidth() - mPlayer.mRadius - 1;

	if (mPlayer.mX + mPlayer.mRadius >= getWindowWidth()) // right of screen
		mPlayer.mX = mPlayer.mRadius + 1;

	if (mPlayer.mY - mPlayer.mRadius <= 0) // bottom of screen
		mPlayer.mY = getWindowHeight() - mPlayer.mRadius - 1;

	if (mPlayer.mY + mPlayer.mRadius >= getWindowHeight()) // top of screen
		mPlayer.mY = mPlayer.mRadius + 1;
}

void AsteroidsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	if (mBall.mX != -1)
	{
		m_2dRenderer->setRenderColour(WHITE);
		m_2dRenderer->drawSprite(m_chest, mBall.mX, mBall.mY, 75.0f, 75.0f, 0.0f);
	}

	//the comets
	for (unsigned int i = 0 ; i < mAst.size(); ++i)
	{
		m_2dRenderer->setRenderColour(mAst[i].mColor);
		m_2dRenderer->drawSprite(m_asteroid, mAst[i].mX, mAst[i].mY, mAst[i].mRadius * 10, mAst[i].mRadius * 10, 0.0f);
	}

	m_2dRenderer->setRenderColour(WHITE);
	//m_2dRenderer->drawCircle(mPlayer.mX, mPlayer.mY, mPlayer.mRadius, 0.0f);

	m_2dRenderer->drawSprite(m_myImage, mPlayer.mX, mPlayer.mY, (float)getWindowWidth() / 20, (float)getWindowHeight() / 15, m_rotation);
	
	
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSprite(m_backing, (float) getWindowWidth() / 2, (float) getWindowHeight() / 2, (float) getWindowWidth(), (float) getWindowHeight(), 0.f, 5.f);

	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f, .65f);
	m_2dRenderer->drawSprite(m_controls, (float) getWindowWidth() - 210, (float) getWindowHeight() - 150, 390, 300, 0.f, 5.f);

	bool soundPlayed = false;

	if (mGameIsOver)
	{
		m_2dRenderer->setRenderColour(YELLOW);
		std::ostringstream os;
		std::ostringstream scoreh;
		os << "Game Over :: Press esc to exit";
		m_2dRenderer->drawText(m_font, os.str().c_str(), 10, 10);
		if (mScore) scoreh << "You scored [ " << mScore << " ] ";
		m_2dRenderer->drawText(m_font, scoreh.str().c_str(), (float) (getWindowWidth() - 300), 10);
	}
	else
	{
		m_2dRenderer->setRenderColour(1.f, 1.f, 1.f, 0.4f);
		std::ostringstream os;
		std::ostringstream scorew;
		os << "Press ESC to quit";
		m_2dRenderer->drawText(m_font, os.str().c_str(), 10, 10);
		if (mScore) scorew << " [ " << mScore << " ] ";
		m_2dRenderer->drawText(m_font, scorew.str().c_str(), (float) (getWindowWidth() - 115), 10);
	}

	// done drawing sprites
	m_2dRenderer->end();
}

void AsteroidsApp::sortAsteroids()
{
	std::sort(mAst.begin(), mAst.end(), [](Comet const &a, Comet const &b) {return a.mY < a.mY; });
}

void AsteroidsApp::endSound()
{

}

void AsteroidsApp::testCreateAsteroid(float a_deltaTime)
{
	static float currentTime, stopCreateTime;
	currentTime += a_deltaTime;
	const float decreaseInterval = 2.0f;
	static float addTime;

	addTime += a_deltaTime;
	if (addTime > decreaseInterval)
	{
		addTime = 0;
		mTimeInterval = max(0.2f, mTimeInterval - 0.2f);
	}

	if (distance(mPlayer.mX, mPlayer.mY, mBall.mX, mBall.mY) < mPlayer.mRadius + mBall.mRadius)
	{
		mPlayer.mRadius = max(mBall.mRadius, mPlayer.mRadius - 1.f);

		mPlayer.mSpeed += 12.f;

		mBall.mX = -1.f;

		mScore += 1;

		stopCreateTime = 1.f;

		m_beep->play();
	}
	stopCreateTime = max(0.f, stopCreateTime - a_deltaTime);

	if (stopCreateTime) return;

	if (currentTime < mTimeInterval) return;
	currentTime = 0;

	Comet cmt;
	cmt.mX = (float)(rand() % (getWindowWidth() - 50) + 25);
	cmt.mY = (float)(getWindowHeight());

	cmt.mAsteroidActive = true;
	cmt.mSpeed = (float)(rand() % 400 +50);
	int color = (int)(cmt.mSpeed / 100);
	switch (color)
	{
	case 0: cmt.mColor = CYAN; break;
	case 4: cmt.mColor = YELLOW; break;
	case 3: cmt.mColor = RED; break;
	case 2: cmt.mColor = ORANGE; break;
	case 1: cmt.mColor = DK_RED; break;
	default: cmt.mColor = DK_BROWN; break;
	}

	cmt.mRadius = 5.0f;
	
	mAst.push_back(cmt);

}

void AsteroidsApp::asteroidUpdate(Comet * a_ast, float a_deltaTime)
{
	a_ast->mY -= a_ast->mSpeed*a_deltaTime;

	if (distance(mPlayer.mX, mPlayer.mY, a_ast->mX, a_ast->mY) < mPlayer.mRadius + a_ast->mRadius)
	{
		mGameIsOver = true;
	}

	if (a_ast->mY < 0)
	{
		a_ast->mAsteroidActive = false;
	}
}
// if the ball is not in play place it in play
void AsteroidsApp::placeBallInPlay()
{
	if (mBall.mX != -1.f) return;

	int countTries = 0;

	while (true) {
		if (countTries++ > 10000) break;

		float x = (float)(rand()%(getWindowWidth() -40) + 20);
		float y = (float)(rand() % (getWindowHeight() - 40) + 20);

		//not on the player
		if (distance(mPlayer.mX, mPlayer.mY, x, y) < mPlayer.mRadius + 20) continue;

		//Or close to any comet
		bool areaOk = true;
		for (unsigned int i = 0; i < mAst.size(); ++i) {
			if (distance(mAst[i].mX, mAst[i].mY, x, y) < mAst[i].mRadius + 20)areaOk = false;
		}
		if (!areaOk) continue;
		
		//Success
		mBall.mX = x;
		mBall.mY = y;
		break;
	}
}

float AsteroidsApp::distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
