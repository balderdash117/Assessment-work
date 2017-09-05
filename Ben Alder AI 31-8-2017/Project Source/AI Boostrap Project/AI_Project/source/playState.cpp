#include "playState.h"
#include <iostream>
#include "AI_ProjectApp.h"
#include "GameStateManager.h"

#include "glm\glm.hpp"
#include <glm\ext.hpp>
#include <Texture.h>
#include <Font.h>
#include <Input.h> 

#include "GameObject.h"
#include "keyboardBehaviour.h"
#include "graph2DRenderer.h"
#include "player.h"
#include "Townspeople.h"
#include "knights.h"
#include "overlayClass.h"

playState::playState(AI_ProjectApp *pApp) :	iGameState(pApp), m_map(nullptr),
											m_background(nullptr), m_app(pApp)
{
	m_map = new aie::Texture("./textures/map.png");
	m_background = new aie::Texture("./textures/level.png");

	setUpGraph();
	setUpEntities();
}

playState::~playState()
{
	m_townsPeople.clear();
	m_knight.clear();

	delete player;
	delete m_graph;
	delete m_graphrenderer;
	delete m_map;
	delete m_background;
}

void playState::update(float deltaTime)
{
	aie::Input *input = aie::Input::getInstance();

#pragma region Pause Logic

	if (getApp()->getGameStateManager()->getTopState() != this)
	{
		return;
	}
	else
#pragma endregion
	{
		// If play state is the top state 
			// ALL YOUR UPDATE LOGIC GOES IN HERE

		//updateGraph();

		float time = deltaTime;

#ifdef DEBUG
		if (time > 0.012)
		{
			time = 0.01;
		}
#endif // DEBUG

		glm::vec2 knightPos = m_knight.front()->getPosition();
		glm::vec2 townspersonPos = m_townsPeople.front()->getPosition();

		UpdateTownsPeople(time, knightPos);
		UpdateKnights(time, townspersonPos);

		//glm::vec2 &playerPos = player->getPosition();

		//if (playerPos.x < 0) player->setPosition(glm::vec2(m_app->getWindowWidth(), playerPos.y));
		//if (playerPos.x > m_app->getWindowWidth()) player->setPosition(glm::vec2(0, playerPos.y));
		//
		//if (playerPos.y < 0) player->setPosition(glm::vec2(playerPos.x, m_app->getWindowHeight()));
		//if (playerPos.y > m_app->getWindowHeight()) player->setPosition(glm::vec2(playerPos.x, 0));

		if (input->wasKeyPressed(aie::INPUT_KEY_P))
		{
			getApp()->getGameStateManager()->pushState("pause");
		}

	}
}

void playState::draw(aie::Renderer2D *renderer)
{
	DrawTownsPeople(renderer);
	DrawKnights(renderer);
	drawMap(renderer);

	if (overlayClass::getGraphShowing())
	{
		drawGraph(renderer);
	}

	renderer->drawText(m_font, "Press ESC to quit", 0, 0);
}

void playState::setUpEntities()
{
	player = new Player(m_app);
	player->setPosition(glm::vec2(m_app->getWindowWidth() / 2, m_app->getWindowHeight() / 2));
	player->setGraph(m_graph);

	auto person = new Townspeople(m_app);
	person->setPosition(glm::vec2(m_app->getWindowWidth() / 2, m_app->getWindowHeight() / 2));
	person->setGraph(m_graph);
	person->setObjectType(0);
	m_townsPeople.push_back(person);

	auto knight = new knights(m_app);
	knight->setPosition(glm::vec2(m_app->getWindowWidth() / 3, m_app->getWindowHeight() / 3));
	knight->setGraph(m_graph);
	knight->setObjectType(1);
	m_knight.push_back(knight);
}

void playState::setUpGraph()
{
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_graph = new Graph2D();
	m_graphrenderer = new Graph2DRenderer();
	m_graphrenderer->SetGraph(m_graph);

	const int Spacing = 15;
	const int xOffSet = 5;
	const int yOffSet = 5;
	const int numRows = m_app->getWindowHeight() / Spacing;
	const int numColumns = m_app->getWindowWidth() / Spacing;

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numColumns; x++)
		{
			glm::vec2 nodePos = glm::vec2(x * Spacing + xOffSet, y * Spacing + yOffSet);

			// Find current pixel (4 bytes = R, G, B, A)
			size_t pixelIndex = (size_t)((m_map->getHeight() - nodePos.y) * m_map->getWidth() + nodePos.x) * 4;

			// If pixel is black (first 3 bytes are 0)
			if (m_map->getPixels()[pixelIndex + 3] == 0)
			{

			}
			else
			{
				m_graph->AddNode(nodePos);
			}
		}
	}

	auto &nodes = m_graph->GetNodes();

	for (auto iter1 = nodes.begin(); iter1 != nodes.end(); iter1++)
	{
		Graph2D::Node *nodeA = (*iter1);
		std::vector<Graph2D::Node *> nearbyNodes;
		m_graph->GetNearbyNodes(nodeA->data, 25.0f, nearbyNodes);

		for (auto iter2 = nearbyNodes.begin(); iter2 != nearbyNodes.end(); iter2++)
		{
			Graph2D::Node *nodeB = (*iter2);
			if (nodeA == nodeB)
			{
				continue;
			}

			float distanceBetweenNodes = glm::length(nodeB->data - nodeA->data);
			m_graph->AddEdge(nodeA, nodeB, false, distanceBetweenNodes);
		}
	}

}

void playState::updateGraph()
{
	aie::Input* input = aie::Input::getInstance();

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		std::vector<Graph2D::Node *> nearbyNodes;
		m_graph->GetNearbyNodes(m_mousePos, 20.0f, nearbyNodes);

		auto addedNode = m_graph->AddNode(m_mousePos);

		for (auto iter = nearbyNodes.begin(); iter != nearbyNodes.end(); iter++)
		{
			float dist = glm::length(addedNode->data - (*iter)->data);
			m_graph->AddEdge((*iter), addedNode, true, dist);
		}
	}
}

void playState::UpdateTownsPeople(float dt, glm::vec2 opponentPos)
{
	for (auto iter = m_townsPeople.begin(); iter != m_townsPeople.end(); iter++)
	{
		(*iter)->update(dt, opponentPos);
	}
}

void playState::UpdateKnights(float dt, glm::vec2 opponentPos)
{
	for (auto iter = m_knight.begin(); iter != m_knight.end(); iter++)
	{
		(*iter)->update(dt, opponentPos);
	}
}

void playState::DrawTownsPeople(aie::Renderer2D *renderer)
{
	for (auto iter = m_townsPeople.begin(); iter != m_townsPeople.end(); iter++)
	{
		(*iter)->draw(renderer);
	}
}

void playState::DrawKnights(aie::Renderer2D *renderer)
{
	for (auto iter = m_knight.begin(); iter != m_knight.end(); iter++)
	{
		(*iter)->draw(renderer);
	}
}

void playState::drawMap(aie::Renderer2D *renderer)
{
	renderer->drawSprite(m_map, 0, 0, 0, 0, 0, 50.f, 0, 0);
	renderer->drawSprite(m_background, 0, 0, 0, 0, 0, 100.f, 0, 0);
}

void playState::drawGraph(aie::Renderer2D *renderer)
{
	aie::Input* input = aie::Input::getInstance();

	int mx, my;
	input->getMouseXY(&mx, &my);
	m_mousePos = glm::vec2(mx, my);

	m_graphrenderer->Draw(renderer);
	//render lines to nodes
	std::vector<Graph2D::Node *> nearbyNodes;
	m_graph->GetNearbyNodes(m_mousePos, 20.0f, nearbyNodes);

	for (auto iter = nearbyNodes.begin(); iter != nearbyNodes.end(); iter++)
	{
		renderer->drawLine(m_mousePos.x, m_mousePos.y, (*iter)->data.x, (*iter)->data.y);
	}
}

aie::Texture playState::getMapTexture()
{
	return *m_map;
}
