#pragma once

#include <map>
#include <vector>

class iGameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void updateStates(float deltaTime);
	void drawGameStates();

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

