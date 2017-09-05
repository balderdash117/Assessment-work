#include "playState.h"
#include <iostream>
#include "GameStateWalkthroughApp.h"

playState::playState(GameStateWalkthroughApp *pApp) :
	iGameState(pApp)
{

}


playState::~playState()
{
}

void playState::update(float deltaTime)
{
	aie::Input *input = aie::Input::getInstance();

	if (getApp()->getGameStateManager()->getTopState() != this)
	{
		return;
	}
	else
	{
		// If play state is the top state (hence pause state is not ontop of it)
		// ALL YOUR UPDATE LOGIC INCLUDING BUT NOT LIMITED TO 

		if (input->wasKeyPressed(aie::INPUT_KEY_P))
		{
			getApp()->getGameStateManager()->pushState("pause");
		}

	}

	//std::cout << "Play - Update" << std::endl;
}

void playState::draw()
{
	//std::cout << "Play - Draw" << std::endl;


	//m_app->GetRenderer()->drawLine(70, 10000, 70, 10000);
	//m_app->GetRenderer()->drawText(m_app->m_font2, "Press ESC to quit", 0, 0);
	//
	//m_app->GetRenderer()->setRenderColour(0xffffffff); //Anything you want naturally coloured
	//m_app->GetRenderer()->drawSprite(m_app->background, ((float)m_app->getWindowWidth() / 2), ((float)m_app->getWindowHeight() / 2),
		//(float)m_app->getWindowWidth(), (float)m_app->getWindowHeight(), 0.f, 50.f);
}