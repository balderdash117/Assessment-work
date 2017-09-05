#include "overlayClass.h"
#include <Input.h>

// Static definition
bool overlayClass::m_showingGraph = false;

overlayClass::overlayClass()
{
}


overlayClass::~overlayClass()
{
}

void overlayClass::update()
{
	aie::Input* input = aie::Input::getInstance();

	if (input->wasKeyPressed(aie::INPUT_KEY_TAB))
	{
		if (m_showingGraph)
			m_showingGraph = false;
		else
			m_showingGraph = true;
	}
}

bool overlayClass::getGraphShowing()
{
	return m_showingGraph;
}
