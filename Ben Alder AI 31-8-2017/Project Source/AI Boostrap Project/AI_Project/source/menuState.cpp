#include "menuState.h"
#include <iostream>
#include "AI_ProjectApp.h"
#include "iGameState.h"
#include "GameStateManager.h"

menuState::menuState(AI_ProjectApp *pApp) :
	iGameState(pApp)
{

}


menuState::~menuState()
{
}

void menuState::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	//std::cout << "Menu - Update" << std::endl;

	float mouseX = (float)input->getMouseX();
	float mouseY = (float)input->getMouseY();

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		if (mouseX > m_app->positionButtonX() - 98 && mouseX < m_app->positionButtonX() + 98)
		{
			//std::cout << "clicked inside thee buttons X pos";
			if (mouseY > m_app->positionButtonY(1) - 27 && mouseY < m_app->positionButtonY(1) + 27)
			{
				//std::cout << " and inside play buttons Y pos";
				m_app->getGameStateManager()->popState();
				m_app->getGameStateManager()->pushState("controls");
			}
			if (mouseY > m_app->positionButtonY(2) - 27 && mouseY < m_app->positionButtonY(2) + 27)
			{
				//std::cout << " and inside options buttons Y pos";
			}
			if (mouseY > m_app->positionButtonY(3) - 27 && mouseY < m_app->positionButtonY(3) + 27)
			{
				//std::cout << " and inside exit buttons Y pos";
					m_app->quit();
			}
			std::cout << std::endl;
		}
	}
}

void menuState::draw(aie::Renderer2D *renderer)
{
	//std::cout << "Menu - Draw" << std::endl;

	renderer->setRenderColour(0, 0, 0); //Anything you want black for colour
	renderer->drawText(m_app->getFont1(), "Code Design" ,((float)m_app->getWindowWidth() / 2) - 192, ((float)m_app->getWindowHeight() / 6) * 4.5f);

	renderer->setRenderColour(0xffffffff); //Anything you want naturally coloured
	renderer->drawSprite(m_app->getBackground(), ((float)m_app->getWindowWidth() / 2), ((float)m_app->getWindowHeight() / 2),
							(float)m_app->getWindowWidth(), (float)m_app->getWindowHeight(), 0.f, 50.f);
	
	renderer->drawSprite(m_app->getPlayButton(), m_app->positionButtonX(), m_app->positionButtonY(1), 0.f, 0.f, 0.f, 40.f);
	renderer->drawSprite(m_app->getOptionsButton(), m_app->positionButtonX(), m_app->positionButtonY(2), 0.f, 0.f, 0.f, 40.f);
	renderer->drawSprite(m_app->getExitButton(), m_app->positionButtonX(), m_app->positionButtonY(3), 0.f, 0.f, 0.f, 40.f);
}


