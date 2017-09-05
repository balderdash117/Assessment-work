#include "SceneGraphApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Utility.h>
#include "Node.h"
#include "SpriteNode.h"
#include "Tank.h"

SceneGraphApp::SceneGraphApp() {

}

SceneGraphApp::~SceneGraphApp() {

}

bool SceneGraphApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_tank = new Tank();
	m_tank->Translate(Vector2(300, 300));
	m_nodes.push_back(m_tank);

	return true;
}

void SceneGraphApp::shutdown() {

	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
	{
		delete (*iter);
	}
	m_nodes.clear();

	
	
	delete m_font;
	delete m_2dRenderer;
}

void SceneGraphApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
	{
		(*iter)->Update(deltaTime);
	}
}

void SceneGraphApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	// loop through the collection of nodes and render everything
	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
	{
		(*iter)->Render(m_2dRenderer);
	}
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}