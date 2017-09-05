#include "knights.h"
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

knights::knights(AI_ProjectApp *pApp) : GameObject(pApp), force(500.f), m_graph(nullptr),
										m_startNode(nullptr), m_endNode(nullptr),
										m_pathFinder(nullptr), m_app(pApp)
{
	setFriction(10.f);

	m_seekBehaviour = new seekBehaviour();
	m_seekBehaviour->isOwnedByGameObject(false);
	m_seekBehaviour->setForceStrength(force);
	m_seekBehaviour->setInnerRadius(20);
	m_seekBehaviour->setOuterRadius(100);
	
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

	setBehaviour(nullptr);
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
	if (getVelocity() == glm::vec2(0, 0))
	{
		//std::cout << "velocity == 0" << std::endl;
	}

	int mx, my;
	static float counter = 0;

	counter++;
	counter += 0.3f;
		aie::Input * input = aie::Input::getInstance();

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

								std::cout << "Knight: " << ++numOfTimes << ". " << size << "      " << sizelast << std::endl;

								m_pathSize = (float)m_pathFinder->getPath().getPath().size();

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
}

//real update
void knights::update(float deltaTime, glm::vec2 opponentPos)
{
	static bool changeBehaviour = false;
	float dist = glm::length2(getPosition() - opponentPos);
	
	if (dist < 25000.f)
	{
		changeBehaviour = true;
	}
	else if (dist > 30000.f)
	{
		changeBehaviour = false;
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

	input->getMouseXY(&mx, &my);

	if (changeBehaviour == false)
	{
		#pragma region Follow Random Path (Wandering)
	
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

							std::cout << "Knight: " << ++numOfTimes << ". " << size << "      " << sizelast << std::endl;

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
		}
#pragma endregion
	}
	else
	{
		m_count = deltaTime;

		std::vector<Graph2D::Node *> nearbyNodes;

		//do
		//{
		//	if (m_count - deltaTime >= 10)
		//		break;

		//	glm::vec2 randomPoint = findRandomPoint();
			m_graph->GetNearbyNodes(opponentPos, 25, nearbyNodes);
		//	++m_count;
		//} while (nearbyNodes.size() == 0);

		std::vector<Graph2D::Node *> knightsNearbyNodes;
		m_graph->GetNearbyNodes(glm::vec2(position.x, position.y), 20, knightsNearbyNodes);

		if (knightsNearbyNodes.empty() == false)
			m_startNode = knightsNearbyNodes[0];

		if (nearbyNodes.empty() == false)
		{
			if (m_endNode == nullptr)
			{
				m_endNode = nearbyNodes[0];
				if (m_startNode == nullptr)
				{
					m_startNode = nullptr;
					m_endNode = nullptr;
					return;
				}
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

						if (m_followPathBehaviour->getPathNodeIndex() == 0)
						{
							m_followPathBehaviour->setPathNodeIndex(1);
						}

						std::cout << "Knight: " << ++numOfTimes << ". " << size << "      " << sizelast << std::endl;

						m_pathSize = (float)m_pathFinder->getPath().getPath().size();

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
	}

	GameObject::update(deltaTime);
}

void knights::draw(aie::Renderer2D * renderer)
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

glm::vec2 knights::findRandomPoint()
{
	srand((unsigned int)time(NULL));

	int x = (int)m_app->returnWindowWidth();
	int y = (int)m_app->returnWindowHeight();

	int posX = (rand() * rand() * (rand() * 5)) % x;
							   
	int posY = (rand() * rand() * (rand() * 5)) % y;

	if (posX < 0)
	{
		posX = posX * -1;
	}

	if (posY < 0)
	{
		posY = posY * -1;
	}

	if (posX > (int)m_app->returnWindowWidth() || posY > (int)m_app->returnWindowHeight())
	{
		findRandomPoint();
	}

	glm::vec2 randPos = glm::vec2(posX, posY);

	return randPos;
}
