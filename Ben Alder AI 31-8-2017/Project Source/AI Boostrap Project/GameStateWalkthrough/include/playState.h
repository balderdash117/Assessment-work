#pragma once
#include "iGameState.h"

class playState :
	public iGameState
{
public:
	playState(GameStateWalkthroughApp *pApp);
	virtual ~playState();

	virtual void update(float deltaTime);
	virtual void draw();
protected:
private:
};

