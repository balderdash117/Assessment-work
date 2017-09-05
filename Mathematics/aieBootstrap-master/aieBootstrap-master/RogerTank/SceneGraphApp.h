#pragma once

#include "Renderer2D.h"
#include <Vector2.h>
#include <Matrix3.h>
#include <Application.h>
#include <vector>

class Node;
class SpriteNode;
class Tank;

struct TankTracks 
{
	Vector2 pt;
	float rotate;
	float time;
};

struct bullet
{
	Vector2 point;
	float rotate;
	float time;
	float speed;
	bool active;
};

class SceneGraphApp : public aie::Application {
public:

	SceneGraphApp();
	virtual ~SceneGraphApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture*		m_wallPaper = nullptr;
	aie::Texture *		m_tankTracks = nullptr;
	aie::Texture *		m_bullets = nullptr;
	
	Tank *m_tank = nullptr;

	std::vector<Node *> m_nodes;
	std::vector <TankTracks> m_tracks;
	std::vector <bullet> m_bullet;
};