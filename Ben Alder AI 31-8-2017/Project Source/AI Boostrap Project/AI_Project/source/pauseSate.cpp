#include "pauseSate.h"
#include <iostream>
#include "AI_ProjectApp.h"
#include "iGameState.h"
#include "GameStateManager.h"

pauseSate::pauseSate(AI_ProjectApp *pApp) :
	iGameState(pApp)
{

}

pauseSate::~pauseSate()
{

}

void pauseSate::update(float deltaTime)
{
	aie::Input *input = aie::Input::getInstance();

	if (input->wasKeyPressed(aie::INPUT_KEY_P))
	{
		m_app->getGameStateManager()->popState();
	}
}

void pauseSate::draw(aie::Renderer2D *renderer)
{
	renderer->drawSprite(m_app->getPauseText(), m_app->positionButtonX(), m_app->positionButtonY(2), 0, 0);
}
