#pragma once
#include "iGameState.h"

class pauseSate :
	public iGameState
{
public:
	pauseSate(AI_ProjectApp *pApp);
	virtual ~pauseSate();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D *renderer);

protected:
private:
};

