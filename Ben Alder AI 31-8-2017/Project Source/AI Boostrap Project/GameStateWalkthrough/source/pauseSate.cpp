#include "pauseSate.h"
#include <iostream>
#include "GameStateWalkthroughApp.h"


pauseSate::pauseSate(GameStateWalkthroughApp *pApp) :
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
			getApp()->getGameStateManager()->popState();

	//std::cout << "pause - Update" << std::endl;
}

void pauseSate::draw()
{
	//std::cout << "pause - Draw" << std::endl;

	m_app->GetRenderer()->drawBox(m_app->positionButtonX(), m_app->positionButtonY(2), 500, 500);

}
