#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <list>
#include <glm\vec2.hpp>

class GameObject;
class Graph2DRenderer;
class Graph2D;
class Player;
class Townspeople;
class knights;
class GameStateManager;
class overlayClass;

class AI_ProjectApp : public aie::Application {
public:

								 AI_ProjectApp();
	virtual						~AI_ProjectApp();

	virtual bool				 startup();
	virtual void				 shutdown();
								 
	virtual void				 update(float deltaTime);
	virtual void				 draw();

	float						 positionButtonX();
	float						 positionButtonY(int buttonNum);

	bool						 showingGraph() { return m_showingGraph; }

	GameStateManager			*getGameStateManager()	{ return m_stateManager; }
	aie::Renderer2D*			 GetRenderer()			{ return m_2dRenderer; }

	aie::Texture				*getBackground()		{ return background; }
	aie::Texture				*getPlayButton()		{ return playButton; }
	aie::Texture				*getOptionsButton()		{ return optionsButton; }
	aie::Texture				*getExitButton()		{ return exitButton; }
	aie::Texture				*getPauseText()			{ return pauseText; }

	aie::Font					*getFont1()				{ return m_font1; }
	aie::Font					*getFont2()				{ return m_font2; }

	float						 returnWindowWidth();
	float						 returnWindowHeight();

protected:


	GameStateManager			*m_stateManager;
	overlayClass				*m_overlay;

	float						 graphToMouseDist;
	float						 m_buttonPosX;
	float						 m_buttonPosY;
	bool						 m_showingGraph;

	aie::Renderer2D				*m_2dRenderer;

	aie::Font					*m_font1;
	aie::Font					*m_font2;

	aie::Texture				*background;
	aie::Texture				*playButton;
	aie::Texture				*optionsButton;
	aie::Texture				*exitButton;
	aie::Texture				*pauseText;

	glm::vec2					 m_mousePos;

	float						 m_windowWidth;
	float						 m_windowHeight;
};