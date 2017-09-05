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

class AI_ProjectApp : public aie::Application {
public:

								 AI_ProjectApp();
	virtual						~AI_ProjectApp();

	virtual bool				 startup();
	virtual void				 shutdown();
								 
	virtual void				 update(float deltaTime);
	virtual void				 draw();

	void						 setUpGraph();
	void						 drawGraph();
	void						 updateGraph();

	void						 UpdateTownsPeople(float dt);
	void						 DrawTownsPeople();

	void						 UpdateKnights(float dt);
	void						 DrawKnights();

	void						 setUpEntities();

	void						 drawMap();

	aie::Texture				 getMapTexture();

protected:
	float						 graphToMouseDist;
	bool						 m_showingGraph;

	aie::Renderer2D*			 m_2dRenderer;
	aie::Font*					 m_font;
	aie::Texture				*m_map;
	aie::Texture				*m_background;

	glm::vec2					 m_mousePos;
								 
	GameObject					*m_gameObj;
	Graph2D						*m_graph;
	Graph2DRenderer				*m_graphrenderer;
								 
	Player						*player = nullptr;
	std::list<Townspeople *>	 m_townsPeople;
	std::list<knights *>		 m_knight;
};