#pragma once

#include <glm/vec2.hpp>
#include "Graph.h"

namespace aie
{
	class Renderer2D;
}

class Graph2D : public Graph<glm::vec2, float>
{
public:

	Graph2D() : Graph() {}
	virtual ~Graph2D() {}


	void GetNearbyNodes(glm::vec2 pos, float radius, 
						std::vector<Graph2D::Node *> &out_collection);

protected:
private:
};

class Graph2DRenderer
{
public:

	Graph2DRenderer();
	~Graph2DRenderer();

	Graph2D		*GetGraph();
	void		 SetGraph(Graph2D * graph);

	void		 Draw(aie::Renderer2D *renderer);

protected:

	Graph2D		*m_graph;

private:
};

