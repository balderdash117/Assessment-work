#include "knights.h"
#include "seekBehaviour.h"
#include "followPathBehaviour.h"
#include "path.h"
#include "graph2DRenderer.h"
#include "pathFinder.h"
#include "Renderer2D.h"
#include "AI_ProjectApp.h"

#include <Input.h>

knights::knights() : GameObject(), force(500.f), m_graph(nullptr),
				   m_startNode(nullptr), m_endNode(nullptr),
				   m_pathFinder(nullptr)
{
	m_seekBehaviour = new seekBehaviour();
	m_seekBehaviour->isOwnedByGameObject(false);
	m_seekBehaviour->setForceStrength(force);
	m_seekBehaviour->setInnerRadius(20);
	m_seekBehaviour->setOuterRadius(100);

	setFriction(10.f);

	m_seekBehaviour->onOuterRadiusEnter([this]()
	{
		m_seekBehaviour->setForceStrength(force / 4);
	});

	m_seekBehaviour->onInnerRadiusEnter([this]()
	{
		setBehaviour(nullptr);
		m_seekBehaviour->setForceStrength(force);
	});

	m_path = new path();

	m_followPathBehaviour = new followPathBehaviour();
	m_followPathBehaviour->isOwnedByGameObject(false);
	m_followPathBehaviour->setPath(m_path);
}

knights::~knights()
{
	setBehaviour(nullptr);

	delete m_path;
	delete m_followPathBehaviour;
	delete m_seekBehaviour;
}

void knights::update(float deltaTime)
{
	int mx, my;

	aie::Input * input = aie::Input::getInstance();

	input->getMouseXY(&mx, &my);

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT) || input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		std::vector<Graph2D::Node *> nearbyNodes;
		m_graph->GetNearbyNodes(glm::vec2(mx, my), 20, nearbyNodes);

		if (nearbyNodes.empty() == false)
		{
			if (m_startNode == nullptr)
			{
				m_startNode = nearbyNodes[0];
			}

			else if (m_endNode == nullptr)
			{
				m_endNode = nearbyNodes[0];
				m_pathFinder = new pathFinder(m_graph);

				// Dijkstras
				 m_pathFinder->findPath(m_startNode, [this](Graph2D::Node *node) {
				 	return node == m_endNode;
				 });

				// astar
				//m_pathFinder->findPath(m_startNode, m_endNode);

				//comment this out to use the debug version of the project
				while (m_pathFinder->pathFound() == false)
				{
					m_pathFinder->updateSearch();
				}

				m_path->clear();
				path p = m_pathFinder->getPath();
				auto pathPoints = p.getPath();
				//start to end
				for (auto iter = pathPoints.rbegin(); iter != pathPoints.rend(); iter++)
				{
					m_path->pushPathSegement((*iter));
				}
				//end to start
				for (auto iter = pathPoints.begin(); iter != pathPoints.end(); iter++)
				{
					m_path->pushPathSegement((*iter));
				}

				if (m_followPathBehaviour->getPathNodeIndex() != 0)
				{
					m_followPathBehaviour->setPathNodeIndex(0);
				}

				setBehaviour(m_followPathBehaviour);
			}

			else
			{
				m_startNode = nullptr;
				m_endNode = nullptr;
				delete m_pathFinder;
				m_pathFinder = nullptr;
			}
		}
	}

#pragma region Debug path stuff


	////Uncomment this to use the debug version of the project
	//if (m_pathFinder != false)
	//{
	//	//add key press condition here if needed
	//	if (m_pathFinder->pathFound() == false)
	//	{
	//		m_pathFinder->updateSearch();
	//	}

	//	m_path->clear();
	//	path p = m_pathFinder->getPath();
	//	auto pathPoints = p.getPath();
	//	//start to end
	//	for (auto iter = pathPoints.rbegin(); iter != pathPoints.rend(); iter++)
	//	{
	//		m_path->pushPathSegement((*iter));
	//	}
	//	//end to start
	//	for (auto iter = pathPoints.begin(); iter != pathPoints.end(); iter++)
	//	{
	//		m_path->pushPathSegement((*iter));
	//	}

	//	setBehaviour(m_followPathBehaviour);
	//}

#pragma endregion

	GameObject::update(deltaTime);
}

void knights::draw(aie::Renderer2D * renderer)
{
	if (m_startNode != nullptr) renderer->drawCircle(m_startNode->data.x, m_startNode->data.y, 4);
	if (m_endNode != nullptr)	renderer->drawCircle(m_endNode->data.x, m_endNode->data.y, 4);

	////uncomment to show the path find
	//////remember to add the key press condition
	//drawPathFind(renderer);

	GameObject::draw(renderer);
}

void knights::setGraph(Graph2D * graph)
{
	m_graph = graph;
}

Graph2D * knights::getGraph()
{
	return m_graph;
}

void knights::drawPathFind(aie::Renderer2D * renderer)
{
	if (m_pathFinder != nullptr)
	{
		// temporary debug drawing of the pathfinder object
		auto &open = m_pathFinder->GetOpen();
		auto &closed = m_pathFinder->GetClosed();

		renderer->setRenderColour(1.0f, 0.0f, 0.0f, 1.0f);
		for (auto iter = open.begin(); iter != open.end(); iter++)
		{
			auto n = (*iter);
			renderer->drawCircle(n->node->data.x, n->node->data.y, 4);
		}

		renderer->setRenderColour(1.0f, 1.0f, 0.0f, 1.0f);
		for (auto iter = closed.begin(); iter != closed.end(); iter++)
		{
			auto n = (*iter);
			renderer->drawCircle(n->node->data.x, n->node->data.y, 4);
		}

		// draw a line from the best node
		if (open.empty() == false)
		{
			renderer->setRenderColour(0xFF7F00FF);

			auto *current = open.back();
			while (current != nullptr)
			{
				auto parent = current->parent;
				if (parent != nullptr)
				{
					renderer->drawLine(current->node->data.x, current->node->data.y, parent->node->data.x, parent->node->data.y, 2.0f);
				}
				current = parent;
			}
		}
	}

	renderer->setRenderColour(0xFFFFFFFF);

}


