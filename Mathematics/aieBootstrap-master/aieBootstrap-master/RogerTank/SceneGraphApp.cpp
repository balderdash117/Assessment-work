#define _USE_MATH_DEFINES
//SpriteNode->Node->Application
//Tank->Node->Application
#include "SceneGraphApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Utility.h>
#include "Tank.h"
#include "SpriteNode.h"
#include <math.h>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

SceneGraphApp::SceneGraphApp() {
}

SceneGraphApp::~SceneGraphApp() {
}

bool SceneGraphApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_wallPaper = new aie::Texture("./sceneGraph/textures/uniBack.jpg");
	m_tankTracks = new aie::Texture("./sceneGraph/textures/tankTracks.png");
	m_bullets = new aie::Texture("./sceneGraph/textures/bullet.png");
	

	float windowWidth = getWindowWidth() / 2;
	float windowHieght = getWindowHeight() / 2;

	m_tank = new Tank();
	m_tank->Translate(Vector2(windowWidth, windowHieght));
	m_nodes.push_back(m_tank);

	return true;
}

void SceneGraphApp::shutdown() {

	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++) {
		delete (*iter);
	}
	m_nodes.clear();
	
	delete m_font;
	delete m_2dRenderer;
	delete m_wallPaper;
	delete m_tankTracks;
	delete m_bullets;
}

void SceneGraphApp::update(float deltaTime) {
	static float sDx, sDy;
	// input example
	aie::Input* input = aie::Input::getInstance();

	static float speed = 1.f;

	m_tank->SetShieldRotate(0.f);

	//static int oldwidth = getWindowWidth();
	//static int oldheight = getWindowHeight();

	//int currentwidth = getWindowWidth();
	//int currentheight = getWindowHeight();

	//if (oldheight != currentheight || oldwidth != currentwidth)
	//{
	//	m_tank->setPos(Vector2(currentwidth / 2, currentheight / 2));
	//	oldwidth = currentwidth;
	//	oldheight = currentheight;
	//}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (input->wasKeyPressed(aie::INPUT_KEY_H))
		speed = 2.f;

	if (input->wasKeyPressed(aie::INPUT_KEY_L))
		speed = 0.5f;

	if (input->wasKeyPressed(aie::INPUT_KEY_O))
		speed = 1.f;

	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);

	Vector2 tankPos = m_tank->GetGlobalPosition();
	
	// grab the position of the tank and make it a vector
	Vector2 mouse = Vector2((float)mouseX, (float)mouseY) - tankPos;

	// calculate angle from vector (the vector from the tank to the mouse)
	float rads = atan2f(mouse.y, mouse.x);

	// move towards the mouse
	
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)) 
	{
		cout << "Mouse left click down" << endl;
		m_tank->SetBaseRotate(rads);
		float bRads = m_tank->GetBaseRotate();
		m_tank->SetTurretRotate(bRads); 

		float dx = (mouseX - tankPos.x) * speed*deltaTime;
		float dy = (mouseY - tankPos.y) * speed*deltaTime;
		m_tank->Translate({ dx, dy });

		if (abs(sDx - tankPos.x) + abs(sDy - tankPos.y) > 5) 
		{
			TankTracks tt;
			 

			tt.pt = m_tank->GetLocalPosition();
			tt.rotate = m_tank->GetBaseRotate();
			tt.time = 0.0f;

			m_tracks.push_back(tt);
			sDx = tankPos.x;
			sDy = tankPos.y;
		}
	} 
	else 
	{
		// the turret only follows the tank
		m_tank->SetTurretRotate(rads); 
	}
	static float currentTime;
	currentTime += deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {
		float l_TimeInterval = 0.0000001f;
		if (currentTime < l_TimeInterval) return;
		currentTime = 0;

		bullet bb;
		bb.point = m_tank->GetLocalPosition();
		bb.rotate = rads;
		bb.time = 0.0f;
		bb.speed = 1000.f;

		m_bullet.push_back(bb);
	}

	for (auto iter = m_bullet.begin(); iter != m_bullet.end(); ++iter) {
		iter->time += deltaTime;
		iter->point.x += cos(iter->rotate)*iter->speed*deltaTime;
		iter->point.y += sin(iter->rotate)*iter->speed*deltaTime;
	}

	for (unsigned int k = m_bullet.size(); k--;) {
		if (m_bullet[k].time >= 10.f) {
			m_bullet.erase(m_bullet.begin() + k);
		}
	}


	// clear 'old' tank tracks - first update the timing
	for (auto iter = m_tracks.begin(); iter != m_tracks.end(); ++iter) {
		iter->time += deltaTime;
	}
	// then erase the ones that have been around a while counting backwards
	for (unsigned int k = m_tracks.size(); k--;) {
		if (m_tracks[k].time >= 0.75f) {
			m_tracks.erase(m_tracks.begin()+k);
		}
	}

	// iterator way for counting backwards
	//for (auto iter = m_tracks.end(); iter != m_tracks.begin(); /* Do nothing */)
	//{
	//	--iter; // Unfortunately, you now need this here
	//	/* Do work */
	//}

	// change the location of the tank or rotation your choice
	//if (input->isKeyDown(aie::INPUT_KEY_W))
	//	m_tank->Translate({ 0.f, .1f });
	//if (input->isKeyDown(aie::INPUT_KEY_A))
	//	m_tank->Translate({ -.1f, 0.f });
	//if (input->isKeyDown(aie::INPUT_KEY_S))
	//	m_tank->Translate({ 0.f, -.1f });
	//if (input->isKeyDown(aie::INPUT_KEY_D))
	//	m_tank->Translate({ .1f, 0.f });

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
	m_2dRenderer->setUVRect(1.f, 1.f, 1.f, 1.f);
	m_2dRenderer->drawSprite(m_wallPaper, (float)getWindowWidth() / 2, (float)getWindowHeight() / 2, (float)getWindowWidth(), (float)getWindowHeight(), 0, 50.f);

	m_2dRenderer->setRenderColour(0xffffff40);
	for (auto iter = m_tracks.begin(); iter != m_tracks.end(); ++iter) {
		m_2dRenderer->drawSprite(m_tankTracks, iter->pt.x, iter->pt.y, (float)m_tankTracks->getWidth(), (float)m_tankTracks->getHeight(), iter->rotate, 2.f);
	}
	m_2dRenderer->setRenderColour(0xff69b4);
	for (auto iter = m_bullet.begin(); iter != m_bullet.end(); ++iter) {
		m_2dRenderer->drawSprite(m_bullets, iter->point.x, iter->point.y, (float)m_bullets->getWidth(), (float)m_bullets->getHeight(), iter->rotate);
	}

	m_2dRenderer->setRenderColour(0xffffffff);

	m_tank->Render(m_2dRenderer);

	// loop through the collection of nodes and render everything
	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++) {
		(*iter)->Render(m_2dRenderer);
	}

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}