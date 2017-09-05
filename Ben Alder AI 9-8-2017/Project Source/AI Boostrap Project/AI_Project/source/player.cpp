#include "player.h"
#include "keyboardBehaviour.h"
#include "seekBehaviour.h"
#include "followPathBehaviour.h"
#include "path.h"
#include "graph2DRenderer.h"
#include "pathFinder.h"
#include "Renderer2D.h"

#include <Input.h>

Player::Player() : GameObject(), force(800.f), m_graph(nullptr),
				   m_startNode(nullptr), m_endNode(nullptr), 
				   m_pathFinder(nullptr)
{																  
	m_KeyboardBehaviour = new KeyboardBehaviour();
	m_KeyboardBehaviour->isOwnedByGameObject(false);

	m_seekBehaviour = new seekBehaviour();
	m_seekBehaviour->isOwnedByGameObject(false);
	m_seekBehaviour->setForceStrength(force);
	m_seekBehaviour->setInnerRadius(20);
	m_seekBehaviour->setOuterRadius(100);



	m_seekBehaviour->onOuterRadiusEnter([this]()
	{
		m_seekBehaviour->setForceStrength(force/4);
	}
	);

	m_seekBehaviour->onInnerRadiusEnter([this]()
	{
		setBehaviour(m_KeyboardBehaviour);
		m_seekBehaviour->setForceStrength(force);
	}
	);
	


	m_fleeBehaviour = new seekBehaviour();
	m_fleeBehaviour->isOwnedByGameObject(false);
	m_fleeBehaviour->setForceStrength(force*-1);
	m_fleeBehaviour->setInnerRadius(60);
	m_fleeBehaviour->setOuterRadius(200);



	m_fleeBehaviour->onOuterRadiusExit([this]() 
	{
		setBehaviour(m_KeyboardBehaviour);
		m_fleeBehaviour->setForceStrength(force);
	}
	);

	m_fleeBehaviour->onInnerRadiusExit([this]()
	{
		m_fleeBehaviour->setForceStrength(force*-1.5f);

	}
	);



	setBehaviour(m_KeyboardBehaviour);
	setFriction(15.f);

	m_seekBehaviour->setKeyboard([this]()
	{
		setBehaviour(m_KeyboardBehaviour);
	}
	);

	m_fleeBehaviour->setHigherSpeed([this]()
	{
		m_fleeBehaviour->setForceStrength(force*-2.1f);
	}
	);


	m_path = new path();

	m_followPathBehaviour = new followPathBehaviour();
	m_followPathBehaviour->isOwnedByGameObject(false);
	m_followPathBehaviour->setPath(m_path);

}

Player::~Player()
{
	setBehaviour(nullptr);

	delete m_path;
	delete m_followPathBehaviour;
	delete m_seekBehaviour;
	delete m_fleeBehaviour;
	delete m_KeyboardBehaviour;
}

void Player::update(float deltaTime)
{
	int mx, my;

	aie::Input * input = aie::Input::getInstance();

	input->getMouseXY(&mx, &my);

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
			m_seekBehaviour->setTarget(glm::vec2(mx,my));
			setBehaviour(m_seekBehaviour);
	}
	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
			m_fleeBehaviour->setTarget(glm::vec2(mx,my));
			setBehaviour(m_fleeBehaviour);
	}

	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_MIDDLE) || input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		std::vector<Graph2D::Node *> nearbyNodes;
		m_graph->GetNearbyNodes(glm::vec2(mx, my), 10, nearbyNodes);

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
				m_pathFinder->findPath(m_startNode, [this](Graph2D::Node *node) {
					return node == m_endNode;
				});

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
				m_endNode	= nullptr;
				delete m_pathFinder;
				m_pathFinder = nullptr;
			}
		}
	}

#pragma region Debug version of pathfinding

	//Uncomment this to use the debug version of the project
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

	if (   getBehaviour() != m_KeyboardBehaviour && 		input->getPressedKeys().empty() == false &&
		input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL))
	{
		setBehaviour(m_KeyboardBehaviour);
		m_seekBehaviour->setForceStrength(100);
	}

	GameObject::update(deltaTime);
}

void Player::draw(aie::Renderer2D * renderer)
{

	if (m_startNode != nullptr) renderer->drawCircle(m_startNode->data.x, m_startNode->data.y, 4);
	if (m_endNode	!= nullptr)	renderer->drawCircle(m_endNode->data.x,	  m_endNode->data.y,   4);

	////uncomment to show the path find
	//////remember to add the key press condition
	//drawPathFind(renderer);

	GameObject::draw(renderer);
}

void Player::setGraph(Graph2D * graph)
{
	m_graph = graph;
}

Graph2D * Player::getGraph()
{
	return m_graph;
}

void Player::drawPathFind(aie::Renderer2D * renderer)
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


