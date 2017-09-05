#pragma once

#include <Application.h>
#include "iostream"
#include "Texture.h"
#include <Input.h>

class GameStateWalkthroughApp;

class iGameState
{
public:
	iGameState(GameStateWalkthroughApp *pApp);
	virtual ~iGameState();

	virtual void update(float deltaTime);
	virtual void draw();

	GameStateWalkthroughApp *getApp() { return m_app; }
protected:
	GameStateWalkthroughApp *m_app;
private:
};