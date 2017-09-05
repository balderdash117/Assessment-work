#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Vector2.h>
#include <Matrix3.h>

#include <vector>

class Node;
class SpriteNode;
class Tank;

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

	Tank *m_tank = nullptr;

	std::vector<Node *> m_nodes;

};