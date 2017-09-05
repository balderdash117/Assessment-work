#include "chooseGameState.h"
#include <iostream>
#include "GameStateWalkthroughApp.h"
#include "GameStateManager.h"

chooseGameState::chooseGameState(GameStateWalkthroughApp * pApp) :
	iGameState(pApp)
{

}

chooseGameState::~chooseGameState()
{

}

void chooseGameState::update(float deltaTime)
{
	static int i;
	i += 1;
	std::cout << "Update choosing state: " << i << std::endl;
}

void chooseGameState::draw()
{
	std::cout << "Drawing choosing state" << std::endl;

	m_app->GetRenderer()->setRenderColour(0xffffffff); //Anything you want naturally coloured
	m_app->GetRenderer()->drawSprite(m_app->background, ((float)m_app->getWindowWidth() / 2), ((float)m_app->getWindowHeight() / 2),
		(float)m_app->getWindowWidth(), (float)m_app->getWindowHeight(), 0.f, 50.f);
}
