#pragma once

#include <Application.h>
#include "iostream"
#include "Texture.h"
#include <Input.h>
#include "Renderer2D.h"

class AI_ProjectApp;

class iGameState
{
public:
	iGameState(AI_ProjectApp *pApp);
	virtual ~iGameState();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D *renderer);

	AI_ProjectApp *getApp() { return m_app; }
protected:
	AI_ProjectApp *m_app;
private:
};