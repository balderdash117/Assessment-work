#pragma once
#include "iGameState.h"

class controlsScreen :
	public iGameState
{
public:
	controlsScreen(AI_ProjectApp *pApp);
	virtual ~controlsScreen();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D *renderer);

protected:
private:
};

