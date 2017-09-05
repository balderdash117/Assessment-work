#pragma once
#include "iGameState.h"

class menuState :
	public iGameState
{
public:
	menuState(AI_ProjectApp *pApp);
	virtual ~menuState();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D *renderer);

protected:
private:
};

