#pragma once

#include "GameObject.h"
#include "graph2DRenderer.h"

class seekBehaviour;
class followPathBehaviour;
class path;
class Graph2D;
class pathFinder;
class followPathBehaviour;

class Townspeople :	public GameObject
{
public:
	Townspeople(AI_ProjectApp *pApp);
	virtual ~Townspeople();

	virtual void			 update(float deltaTime);
	void					 update(float deltaTime, glm::vec2 opponentPos);

	virtual void			 draw(aie::Renderer2D *renderer);

	void					 setGraph(Graph2D *graph);
	Graph2D				    *getGraph();

	void					 drawPathFind(aie::Renderer2D *renderer);

	glm::vec2				 findRandomPoint();

	void					 setRandomPosition(float deltaTime);

protected:

	seekBehaviour			*m_seekBehaviour;
	seekBehaviour			*m_fleeBehaviour;
	followPathBehaviour		*m_followPathBehaviour;

	Graph2D					*m_graph;
	path					*m_path;
	pathFinder				*m_pathFinder;

	Graph2D::Node			*m_startNode;
	Graph2D::Node			*m_endNode;

	float					 force;
	float					 m_count;

	glm::vec2				 m_randomPoint;

	AI_ProjectApp		    *m_app;

private:
};

