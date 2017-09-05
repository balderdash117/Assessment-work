#pragma once
#include "iGameState.h"
#include "Renderer2D.h"
#include <list>
#include <glm\vec2.hpp>

class GameObject;
class Graph2DRenderer;
class Graph2D;
class Player;
class Townspeople;
class knights;

class playState :
	public iGameState
{
public:
	playState(AI_ProjectApp *pApp);
	virtual ~playState();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D *renderer);

	void						 setUpEntities();
	void						 setUpGraph();

	void						 updateGraph();
	void						 UpdateTownsPeople(float dt, glm::vec2 opponentPos);
	void						 UpdateKnights(float dt, glm::vec2 opponentPos);

	void						 DrawTownsPeople(aie::Renderer2D *renderer);
	void						 DrawKnights(aie::Renderer2D *renderer);
	void						 drawMap(aie::Renderer2D *renderer);
	void						 drawGraph(aie::Renderer2D *renderer);


	aie::Texture				 getMapTexture();

protected:
	glm::vec2					 m_mousePos;

	aie::Texture				*m_map;
	aie::Texture				*m_background;
	aie::Font					*m_font;

	GameObject					*m_gameObj;
	Graph2D						*m_graph;
	Graph2DRenderer				*m_graphrenderer;
	
	Player						*player = nullptr;
	std::list<Townspeople *>	 m_townsPeople;
	std::list<knights *>		 m_knight;

	AI_ProjectApp				*m_app;

private:
};

