#include "SpalshState.h"
#include <iostream>
#include "GameStateWalkthroughApp.h"
#include "GameStateManager.h"

SplashState::SplashState(GameStateWalkthroughApp *pApp) :
	iGameState(pApp)
{
}


SplashState::~SplashState()
{
}

void SplashState::update(float deltaTime)
{
	m_splashtimer -= deltaTime;
	if ( m_splashtimer < 0)
	{
		m_splashtimer = 5.0f;

		m_app->getGameStateManager()->popState();
		m_app->getGameStateManager()->pushState("menu");
	}

	m_timePassed += deltaTime;
	m_x = sin(m_timePassed * 10.f) * 30.f + m_app->getWindowWidth() / 2.f;
	m_y = cos(m_timePassed * 10.f) * 30.f + m_app->getWindowHeight() / 5.f ;
}

void SplashState::draw()
{
	std::cout << "Loading" << std::endl;

	m_app->GetRenderer()->setRenderColour(0, 0, 0);
	m_app->GetRenderer()->drawCircle(m_x, m_y + 125, 15);
	m_app->GetRenderer()->drawText(m_app->m_font1, "Loading", ((float)m_app->getWindowWidth() / 2) - 128.f, (float)m_app->getWindowHeight() / 2);
	m_app->GetRenderer()->setRenderColour(0xffffffff);
	m_app->GetRenderer()->drawSprite(m_app->background, ((float)m_app->getWindowWidth() / 2), ((float)m_app->getWindowHeight() / 2), 
															(float)m_app->getWindowWidth(), (float)m_app->getWindowHeight(), 0.f , 50.f);
//inferior method
	////switch ((int)m_splashtimer % 5)
	////{
	////case 1: 
	////	m_app->GetRenderer()->drawBox((float)m_app->getWindowWidth() / 2, 250, 
	////								((float)m_app->getWindowWidth() / 7) + 300, (float)m_app->getWindowHeight() / 30);
	////	break;
	////case 2:
	////	m_app->GetRenderer()->drawBox((float)m_app->getWindowWidth() / 2, 250,
	////								((float)m_app->getWindowWidth() / 7) + 225, (float)m_app->getWindowHeight() / 30);
	////	break;
	////case 3:
	////	m_app->GetRenderer()->drawBox((float)m_app->getWindowWidth() / 2, 250,
	////								((float)m_app->getWindowWidth() / 7) + 150, (float)m_app->getWindowHeight() / 30);
	////	break;
	////case 4:
	////	m_app->GetRenderer()->drawBox((float)m_app->getWindowWidth() / 2, 250,
	////								((float)m_app->getWindowWidth() / 7) + 75, (float)m_app->getWindowHeight() / 30);
	////	break;
	////default:
	////	m_app->GetRenderer()->drawBox((float)m_app->getWindowWidth() / 2, 250,
	////								((float)m_app->getWindowWidth() / 7) + 375, (float)m_app->getWindowHeight() / 30);
	////	break;
	////}
}
