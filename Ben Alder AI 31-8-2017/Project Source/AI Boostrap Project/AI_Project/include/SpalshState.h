#pragma once
#include "iGameState.h"

class SplashState :	public iGameState
{
public:
	SplashState(AI_ProjectApp *pApp);
	virtual ~SplashState();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D *renderer);
protected:
	float m_splashtimer = 5.f;
	float m_timePassed = 0.f;

	float m_x, m_y;
private:
};

