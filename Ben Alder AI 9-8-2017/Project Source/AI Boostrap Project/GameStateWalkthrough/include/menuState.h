#pragma once
#include "iGameState.h"

class menuState :
	public iGameState
{
public:
	menuState(GameStateWalkthroughApp *pApp);
	virtual ~menuState();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
private:
};

