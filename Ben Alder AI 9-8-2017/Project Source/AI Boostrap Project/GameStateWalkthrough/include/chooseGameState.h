#pragma once
#include "iGameState.h"
class chooseGameState :
	public iGameState
{
public:
	chooseGameState(GameStateWalkthroughApp *pApp);
	virtual ~chooseGameState();

	virtual void update(float deltaTime);
	virtual void draw();
};

