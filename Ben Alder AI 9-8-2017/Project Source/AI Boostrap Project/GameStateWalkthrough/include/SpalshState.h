#pragma once
#include "iGameState.h"
class SplashState :
	public iGameState
{
public:
	SplashState(GameStateWalkthroughApp *pApp);
	virtual ~SplashState();

	virtual void update(float deltaTime);
	virtual void draw();
protected:
	float m_splashtimer = 5.f;
	float m_timePassed = 0.f;

	float m_x, m_y;
private:
};

