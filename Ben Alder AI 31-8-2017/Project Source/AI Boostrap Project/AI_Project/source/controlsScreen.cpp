#include "controlsScreen.h"
#include <iostream>
#include "AI_ProjectApp.h"
#include "iGameState.h"
#include "GameStateManager.h"

controlsScreen::controlsScreen(AI_ProjectApp *pApp) :
	iGameState(pApp)
{

}

controlsScreen::~controlsScreen()
{


}

void controlsScreen::update(float deltaTime)
{
	m_app->getGameStateManager()->popState();
	m_app->getGameStateManager()->pushState("play");
}

void controlsScreen::draw(aie::Renderer2D * renderer)
{

}
