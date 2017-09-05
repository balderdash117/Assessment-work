#pragma once

#include "GameObject.h"
#include "graph2DRenderer.h"

class KeyboardBehaviour;
class seekBehaviour;
class followPathBehaviour;
class path;
class Graph2D;
class pathFinder;

class Player : public GameObject
{
public:
							 Player();
	virtual				    ~Player();
						    
	virtual void			 update(float deltaTime);
	virtual void			 draw(aie::Renderer2D *renderer);
						    
	void					 setGraph(Graph2D *graph);
	Graph2D				    *getGraph();

	void					 drawPathFind(aie::Renderer2D * renderer);

protected: 

	KeyboardBehaviour		*m_KeyboardBehaviour;
	seekBehaviour			*m_seekBehaviour;
	seekBehaviour			*m_fleeBehaviour;
	followPathBehaviour		*m_followPathBehaviour;

	Graph2D					*m_graph;
	path					*m_path;
	pathFinder				*m_pathFinder;

	Graph2D::Node			*m_startNode;
	Graph2D::Node			*m_endNode;

	float					force;

private:
};
