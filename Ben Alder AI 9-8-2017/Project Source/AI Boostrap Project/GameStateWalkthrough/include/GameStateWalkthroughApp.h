#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Input.h"
#include "GameStateManager.h"

class GameStateManager;

class GameStateWalkthroughApp : public aie::Application {
public:

	GameStateWalkthroughApp();
	virtual ~GameStateWalkthroughApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	aie::Renderer2D* GetRenderer();
	GameStateManager *getGameStateManager();

	aie::Font*			m_font1;
	aie::Font*			m_font2;
	aie::Texture*		background;
	aie::Texture*       playButton;
	aie::Texture*       optionsButton;
	aie::Texture*       exitButton;

	float positionButtonX();
	float positionButtonY(int buttonNum);

	GameStateManager *Get_GSM();

protected:
	float buttonPosX;
	float buttonPosY;

	GameStateManager *m_GameStateManager = nullptr;

	aie::Renderer2D*	m_2dRenderer;
	
};