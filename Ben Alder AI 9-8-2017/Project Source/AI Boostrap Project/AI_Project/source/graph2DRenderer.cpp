#include "graph2DRenderer.h"
#include <Renderer2D.h>
#include <glm\glm.hpp>

Graph2DRenderer::Graph2DRenderer()
{

}

Graph2DRenderer::~Graph2DRenderer()
{

}

Graph2D * Graph2DRenderer::GetGraph()
{
	return m_graph;
}

void Graph2DRenderer::SetGraph(Graph2D * graph)
{
	m_graph = graph;
}

void Graph2DRenderer::Draw(aie::Renderer2D * renderer)
{
	renderer->setRenderColour(.5f, .5f, 1.f, 0.25f);

	auto &nodes = m_graph->GetNodes();

	for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		Graph2D::Node *node(*iter);
		renderer->drawCircle(node->data.x, node->data.y, 8);
	}

	for (auto eiter = nodes.begin(); eiter != nodes.end(); eiter++)
	{
		Graph2D::Node *nodeA = (*eiter);

		for (auto niter = nodeA->edges.begin(); niter != nodeA->edges.end(); niter++)
		{
			Graph2D::Node *nodeB = (*niter).to;
			renderer->drawLine(nodeA->data.x, nodeA->data.y, nodeB->data.x, nodeB->data.y);
		}
	}

	renderer->setRenderColour(1.f, 1.f, 1.f, 1.f);
}

void Graph2D::GetNearbyNodes(glm::vec2 pos, float radius, std::vector<Graph2D::Node*>& out_collection)
{
	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
	{
		Graph2D::Node *node = (*iter);

		float dist = glm::length(node->data - pos);
		if (dist < radius)
		{
			out_collection.push_back(node);
		}
	}
}
