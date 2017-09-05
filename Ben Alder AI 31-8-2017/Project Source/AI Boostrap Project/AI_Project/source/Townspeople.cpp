#include "Townspeople.h"
#include "seekBehaviour.h"
#include "followPathBehaviour.h"
#include "path.h"
#include "graph2DRenderer.h"
#include "pathFinder.h"
#include "Renderer2D.h"
#include "AI_ProjectApp.h"
#include "overlayClass.h"

#include "glm\glm.hpp"
#include <glm\ext.hpp>
#include <Input.h>
#include <time.h>
#include <iostream>

Townspeople::Townspeople(AI_ProjectApp *pApp) : GameObject(pApp), force(500.f), m_graph(nullptr),
												m_startNode(nullptr), m_endNode(nullptr), 
												m_pathFinder(nullptr), m_app(pApp)
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

Townspeople::~Townspeople()
{
	setBehaviour(nullptr);

	delete m_path;
	delete m_followPathBehaviour;
	delete m_seekBehaviour;
}

void Townspeople::update(float deltaTime)
{
#pragma region Old Update
//
//	int mx, my;
//
//	aie::Input * input = aie::Input::getInstance();
//
//	input->getMouseXY(&mx, &my);
//
//	if (input->wasKeyPressed(aie::INPUT_KEY_M))
//	{
//		setRandomPosition(deltaTime);
//	}
//
//	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT) || input->wasKeyPressed(aie::INPUT_KEY_ENTER))
//	{
//		std::vector<Graph2D::Node *> nearbyNodes;
//		m_graph->GetNearbyNodes(glm::vec2(mx, my), 10, nearbyNodes);
//
//		if (nearbyNodes.empty() == false)
//		{
//			if (m_startNode == nullptr)
//			{
//				m_startNode = nearbyNodes[0];
//			}
//
//			else if (m_endNode == nullptr)
//			{
//				m_endNode = nearbyNodes[0];
//
//				m_pathFinder = new pathFinder(m_graph);
//
//				// Dijkstras
//				// m_pathFinder->findPath(m_startNode, [this](Graph2D::Node *node) {
//				// 	return node == m_endNode;
//				// });
//
//				// astar
//				m_pathFinder->findPath(m_startNode, m_endNode);
//
//				//comment this out to use the debug version of the project
//				while (m_pathFinder->pathFound() == false)
//				{
//					m_pathFinder->updateSearch();
//				}
//
//				m_path->clear();
//				path p = m_pathFinder->getPath();
//				auto pathPoints = p.getPath();
//				//start to end
//				for (auto iter = pathPoints.rbegin(); iter != pathPoints.rend(); iter++)
//				{
//					m_path->pushPathSegement((*iter));
//				}
//
//				//end to start
//				for (auto iter = pathPoints.begin(); iter != pathPoints.end(); iter++)
//				{
//					m_path->pushPathSegement((*iter));
//				}
//
//				if (m_followPathBehaviour->getPathNodeIndex() != 0)
//				{
//					m_followPathBehaviour->setPathNodeIndex(0);
//				}
//
//				setBehaviour(m_followPathBehaviour);
//			}
//
//			else
//			{
//				m_startNode = nullptr;
//				m_endNode = nullptr;
//				delete m_pathFinder;
//				m_pathFinder = nullptr;
//
//				setBehaviour(nullptr);
//			}
//		}
//	}
//
//#pragma region Debug path stuff
//
//
//	////Uncomment this to use the debug version of the project
//	//if (m_pathFinder != false)
//	//{
//	//	//add key press condition here if needed
//	//	if (m_pathFinder->pathFound() == false)
//	//	{
//	//		m_pathFinder->updateSearch();
//	//	}
//
//	//	m_path->clear();
//	//	path p = m_pathFinder->getPath();
//	//	auto pathPoints = p.getPath();
//	//	//start to end
//	//	for (auto iter = pathPoints.rbegin(); iter != pathPoints.rend(); iter++)
//	//	{
//	//		m_path->pushPathSegement((*iter));
//	//	}
//	//	//end to start
//	//	for (auto iter = pathPoints.begin(); iter != pathPoints.end(); iter++)
//	//	{
//	//		m_path->pushPathSegement((*iter));
//	//	}
//
//	//	setBehaviour(m_followPathBehaviour);
//	//}
//
//#pragma endregion
//
//	GameObject::update(deltaTime);
#pragma endregion
#pragma region New Update

if (getVelocity() == glm::vec2(0, 0))
{
	//std::cout << "velocity == 0" << std::endl;
}

int mx, my;
static float counter = 0;

counter++;
counter += 0.3f;
aie::Input * input = aie::Input::getInstance();

if (input->wasKeyPressed(aie::INPUT_KEY_0))
{
	setPosition(glm::vec2(m_app->getWindowWidth() / 2, m_app->getWindowHeight() / 2));
}

input->getMouseXY(&mx, &my);

#pragma region FollowPathStuff

if (getBehaviour() == nullptr || getVelocity() == glm::vec2(0, 0))
{
	m_count = deltaTime;

	std::vector<Graph2D::Node *> nearbyNodes;

	do
	{
		if (m_count - deltaTime >= 10)
			break;

		glm::vec2 randomPoint = findRandomPoint();
		m_graph->GetNearbyNodes(randomPoint, 40, nearbyNodes);
		++m_count;
	} while (nearbyNodes.size() == 0);

	std::vector<Graph2D::Node *> knightsNearbyNodes;
	m_graph->GetNearbyNodes(glm::vec2(position.x, position.y), 15, knightsNearbyNodes);

	if (knightsNearbyNodes.empty() == false)
		m_startNode = knightsNearbyNodes[0];

	if (nearbyNodes.empty() == false)
	{
		if (m_endNode == nullptr)
		{
			m_endNode = nearbyNodes[0];

			if (m_startNode->data != m_endNode->data)
			{
				m_pathFinder = new pathFinder(m_graph);

				// Dijkstras
				m_pathFinder->findPath(m_startNode, [this](Graph2D::Node *node) {
					return node == m_endNode;
				});

				// astar
				//m_pathFinder->findPath(m_startNode, m_endNode);

				while (m_pathFinder->pathFound() == false)
				{
					m_pathFinder->updateSearch();
				}

				if (m_pathFinder->getPath().getPath().size() != 0)
				{
					m_path->clear();
					path p = m_pathFinder->getPath();
					auto pathPoints = p.getPath();
					//start to end
					for (auto iter = pathPoints.rbegin(); iter != pathPoints.rend(); iter++)
					{
						m_path->pushPathSegement((*iter));
					}

					if (m_followPathBehaviour->getPathNodeIndex() != 0)
					{
						m_followPathBehaviour->setPathNodeIndex(0);
					}

					static float numOfTimes = 0;

					static float sizelast = (float)m_path->getPath().size();

					float size;

					if (numOfTimes != 0)
					{
						size = (float)m_path->getPath().size();

						sizelast += size;
					}
					else
					{
						size = sizelast;
					}

					std::cout << "Townsperson: " << ++numOfTimes << ". " << size << "      " << sizelast << std::endl;

					setBehaviour(m_followPathBehaviour);
				}
				delete m_pathFinder;
				m_pathFinder = nullptr;
			}
			else
			{
				setVelocity(glm::vec2(0, 0));
				setBehaviour(nullptr);
			}

			m_startNode = nullptr;
			m_endNode = nullptr;
		}
	}
#pragma endregion

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

}
GameObject::update(deltaTime);
#pragma endregion

}

void Townspeople::update(float deltaTime, glm::vec2 opponentPos)
{
#pragma region Old Update
	//
	//	int mx, my;
	//
	//	aie::Input * input = aie::Input::getInstance();
	//
	//	input->getMouseXY(&mx, &my);
	//
	//	if (input->wasKeyPressed(aie::INPUT_KEY_M))
	//	{
	//		setRandomPosition(deltaTime);
	//	}
	//
	//	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT) || input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	//	{
	//		std::vector<Graph2D::Node *> nearbyNodes;
	//		m_graph->GetNearbyNodes(glm::vec2(mx, my), 10, nearbyNodes);
	//
	//		if (nearbyNodes.empty() == false)
	//		{
	//			if (m_startNode == nullptr)
	//			{
	//				m_startNode = nearbyNodes[0];
	//			}
	//
	//			else if (m_endNode == nullptr)
	//			{
	//				m_endNode = nearbyNodes[0];
	//
	//				m_pathFinder = new pathFinder(m_graph);
	//
	//				// Dijkstras
	//				// m_pathFinder->findPath(m_startNode, [this](Graph2D::Node *node) {
	//				// 	return node == m_endNode;
	//				// });
	//
	//				// astar
	//				m_pathFinder->findPath(m_startNode, m_endNode);
	//
	//				//comment this out to use the debug version of the project
	//				while (m_pathFinder->pathFound() == false)
	//				{
	//					m_pathFinder->updateSearch();
	//				}
	//
	//				m_path->clear();
	//				path p = m_pathFinder->getPath();
	//				auto pathPoints = p.getPath();
	//				//start to end
	//				for (auto iter = pathPoints.rbegin(); iter != pathPoints.rend(); iter++)
	//				{
	//					m_path->pushPathSegement((*iter));
	//				}
	//
	//				//end to start
	//				for (auto iter = pathPoints.begin(); iter != pathPoints.end(); iter++)
	//				{
	//					m_path->pushPathSegement((*iter));
	//				}
	//
	//				if (m_followPathBehaviour->getPathNodeIndex() != 0)
	//				{
	//					m_followPathBehaviour->setPathNodeIndex(0);
	//				}
	//
	//				setBehaviour(m_followPathBehaviour);
	//			}
	//
	//			else
	//			{
	//				m_startNode = nullptr;
	//				m_endNode = nullptr;
	//				delete m_pathFinder;
	//				m_pathFinder = nullptr;
	//
	//				setBehaviour(nullptr);
	//			}
	//		}
	//	}
	//
	//#pragma region Debug path stuff
	//
	//
	//	////Uncomment this to use the debug version of the project
	//	//if (m_pathFinder != false)
	//	//{
	//	//	//add key press condition here if needed
	//	//	if (m_pathFinder->pathFound() == false)
	//	//	{
	//	//		m_pathFinder->updateSearch();
	//	//	}
	//
	//	//	m_path->clear();
	//	//	path p = m_pathFinder->getPath();
	//	//	auto pathPoints = p.getPath();
	//	//	//start to end
	//	//	for (auto iter = pathPoints.rbegin(); iter != pathPoints.rend(); iter++)
	//	//	{
	//	//		m_path->pushPathSegement((*iter));
	//	//	}
	//	//	//end to start
	//	//	for (auto iter = pathPoints.begin(); iter != pathPoints.end(); iter++)
	//	//	{
	//	//		m_path->pushPathSegement((*iter));
	//	//	}
	//
	//	//	setBehaviour(m_followPathBehaviour);
	//	//}
	//
	//#pragma endregion
	//
	//	GameObject::update(deltaTime);
#pragma endregion
#pragma region New Update

	static bool changeBehaviour = false;
	float dist = glm::length2(getPosition() - opponentPos);
	
	if (dist < 25000.f)
	{
		changeBehaviour = true;
		setFriction(7);
	}
	else if (dist > 30000.f)
	{
		changeBehaviour = false;
		setFriction(10);
	}

	if (getVelocity() == glm::vec2(0, 0))
	{
		//std::cout << "velocity == 0" << std::endl;
	}

	int mx, my;
	static float counter = 0;

	counter++;
	counter += 0.3f;
	aie::Input * input = aie::Input::getInstance();

	if (input->wasKeyPressed(aie::INPUT_KEY_0))
	{
		setPosition(glm::vec2(m_app->getWindowWidth() / 2, m_app->getWindowHeight() / 2));
	}

	input->getMouseXY(&mx, &my);

#pragma region FollowPathStuff

	if (getBehaviour() == nullptr || getVelocity() == glm::vec2(0, 0))
	{
		m_count = deltaTime;

		std::vector<Graph2D::Node *> nearbyNodes;

		do
		{
			if (m_count - deltaTime >= 10)
				break;

			glm::vec2 randomPoint = findRandomPoint();
			m_graph->GetNearbyNodes(randomPoint, 40, nearbyNodes);
			++m_count;
		} while (nearbyNodes.size() == 0);

		std::vector<Graph2D::Node *> knightsNearbyNodes;
		m_graph->GetNearbyNodes(glm::vec2(position.x, position.y), 25, knightsNearbyNodes);

		if (knightsNearbyNodes.empty() == false)
			m_startNode = knightsNearbyNodes[0];

		if (nearbyNodes.empty() == false)
		{
			if (m_endNode == nullptr)
			{
				m_endNode = nearbyNodes[0];

				if (m_startNode->data != m_endNode->data)
				{
					m_pathFinder = new pathFinder(m_graph);

					// Dijkstras
					m_pathFinder->findPath(m_startNode, [this](Graph2D::Node *node) {
						return node == m_endNode;
					});

					// astar
					//m_pathFinder->findPath(m_startNode, m_endNode);

					while (m_pathFinder->pathFound() == false)
					{
						m_pathFinder->updateSearch();
					}

					if (m_pathFinder->getPath().getPath().size() != 0)
					{
						m_path->clear();
						path p = m_pathFinder->getPath();
						auto pathPoints = p.getPath();
						//start to end
						for (auto iter = pathPoints.rbegin(); iter != pathPoints.rend(); iter++)
						{
							m_path->pushPathSegement((*iter));
						}

						if (m_followPathBehaviour->getPathNodeIndex() != 0)
						{
							m_followPathBehaviour->setPathNodeIndex(0);
						}

						static float numOfTimes = 0;

						static float sizelast = (float)m_path->getPath().size();

						float size;

						if (numOfTimes != 0)
						{
							size = (float)m_path->getPath().size();

							sizelast += size;
						}
						else
						{
							size = sizelast;
						}

						std::cout << "Townsperson: " << ++numOfTimes << ". " << size << "      " << sizelast << std::endl;

						setBehaviour(m_followPathBehaviour);
					}
					delete m_pathFinder;
					m_pathFinder = nullptr;
				}
				else
				{
					setVelocity(glm::vec2(0, 0));
					setBehaviour(nullptr);
				}

				m_startNode = nullptr;
				m_endNode = nullptr;
			}
		}
#pragma endregion

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

	}
	GameObject::update(deltaTime);
#pragma endregion
}

void Townspeople::draw(aie::Renderer2D * renderer)
{
	if (overlayClass::getGraphShowing())
	{
		if (m_startNode != nullptr) renderer->drawCircle(m_startNode->data.x, m_startNode->data.y, 4);
		if (m_endNode != nullptr)	renderer->drawCircle(m_endNode->data.x, m_endNode->data.y, 4);
	}

	////uncomment to show the path find
	//////remember to add the key press condition
	//drawPathFind(renderer);

	GameObject::draw(renderer);
}

void Townspeople::setGraph(Graph2D * graph)
{
	m_graph = graph;
}

Graph2D * Townspeople::getGraph()
{
	return m_graph;
}

void Townspeople::drawPathFind(aie::Renderer2D * renderer)
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

glm::vec2 Townspeople::findRandomPoint()
{
	srand((unsigned int)time(NULL));

	int x = (int)m_app->returnWindowWidth();
	int y = (int)m_app->returnWindowHeight();

	int posX = (rand() * rand() * (rand() * 4)) % x;
					
	int posY = (rand() * rand() * (rand() * 4)) % y;

	if (posX < 0)
	{
		posX = posX * -1;
	}

	if (posY < 0)
	{
		posY = posY * -1;
	}

	if (posX >(int)m_app->returnWindowWidth() || posY >(int)m_app->returnWindowHeight())
	{
		findRandomPoint();
	}

	glm::vec2 randPos = glm::vec2(posX, posY);

	return randPos;
}

void Townspeople::setRandomPosition(float deltaTime)
{
	m_count = deltaTime;

	std::vector<Graph2D::Node *> nearestNodes;

	do
	{
		if (m_count - deltaTime >= 10)
			break;

		m_randomPoint = findRandomPoint();
		m_graph->GetNearbyNodes(m_randomPoint, 2, nearestNodes);
		++m_count;
	} while (nearestNodes.size() == 0);

	if (nearestNodes.size() != 0)
		setPosition(m_randomPoint);

}
