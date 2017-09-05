#pragma once
#include "iGameState.h"
class pauseSate :
	public iGameState
{
public:
	pauseSate(GameStateWalkthroughApp *pApp);
	virtual ~pauseSate();

	virtual void update(float deltaTime);
	virtual void draw();
protected:
private:
};

