#pragma once

#include <map>
#include <vector>

#include "Renderer2D.h"

class iGameState;
class AI_ProjectApp;

class GameStateManager
{
public:
	GameStateManager(AI_ProjectApp *pApp);
	~GameStateManager();

	void updateStates(float deltaTime);
	void drawGameStates(aie::Renderer2D	*renderer);

	void setState(const char *name, iGameState *state);
	void pushState(const char *name);
	void popState();

	iGameState *getTopState() { return m_states.back(); }

protected:

	void processCommands();

	void dosetState(const char *name, iGameState *state);
	void dopushState(const char *name);
	void dopopState();

	std::map <const char *, iGameState *> m_availableState;
	std::vector<iGameState *> m_states;

	enum class eCommands
	{
		set_state,
		push_state,
		pop_state
	};

	struct commands
	{
		eCommands cmd;
		const char *name;
		iGameState *state;
	};

	std::vector<commands> m_commands;

private:
};

