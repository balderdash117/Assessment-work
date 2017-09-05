#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>
#include "Audio.h"
using std::vector;

enum Colors {
	RED = 0xff0000ff, DK_RED = 0x800000ff, YELLOW = 0xffff00ff, ORANGE = 0xff8000ff, GREY = 0xC0C0C0ff, DK_GREY = 0x808080ff,
	GREEN = 0x00ff00ff, DK_GREEN = 0x008000ff, CYAN = 0x00ffffff, DK_CYAN = 0x008080ff, BLUE = 0x0000ffff, DK_BLUE = 0x000080ff,
	PURPLE = 0x8034f280, WHITE = 0xffffffff, DK_BROWN = 0x993300, BROWN = 0xCC6600
};
struct Comet
{
	bool	mAsteroidActive;	//has it been created
	float	mX;					//where is it x coord
	float	mY;					//where is it y coord
	float	mRadius;			//for the size
	float	mSpeed;				//speed of the asteroid 0 - 4 ( 0 is  fastest )
	Colors	mColor;				//color of the comet
};
struct Player
{
	float	mX;					//where is it x coord
	float	mY;					//where is it y coord
	float	mSpeed;				//speed of the player
	float	mRadius;			//for the size
};
struct ball
{
	float	mX;					//where is it x coord
	float	mY;					//where is it y coord
	float	mRadius;			//for the size
};
class AsteroidsApp : public aie::Application {
public:

	AsteroidsApp();
	virtual ~AsteroidsApp() = default;

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void endSound();
	void sortAsteroids();
	void testCreateAsteroid(float deltaTime);
	void asteroidUpdate(Comet *a_ast, float deltaTime);
	void placeBallInPlay();
	float distance(float x1, float y1, float x2, float y2);

protected:
	bool	mGameIsOver;
	float	mTimeInterval;
	float	mTimer;
	float	mScore;
	vector	<Comet> mAst;
	Player	mPlayer;
	ball	mBall;

	//aie::Texture*		m_texture;
	//aie::Texture*		m_playerTexture;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture*		m_myImage;
	aie::Texture*       m_asteroid;
	aie::Texture*       m_backing;
	aie::Texture*		m_controls;
	aie::Texture*		m_chest;
	aie::Audio*			m_halo;
	aie::Audio*			m_beep;
	aie::Audio*			m_gameOver;
	aie::Audio*			m_destroy;
	

	float m_xPos = 100.0f;
	float m_yPos = 100.0f;
	float m_rotation = 0.0f;

	double m_lastScrollValue = 0.0;
};