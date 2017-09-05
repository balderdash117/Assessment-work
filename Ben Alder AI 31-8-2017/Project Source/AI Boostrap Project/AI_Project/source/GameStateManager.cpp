#include "GameStateManager.h"
#include "iGameState.h"
#include "overlayClass.h"

GameStateManager::GameStateManager(AI_ProjectApp *pApp)
{

}

GameStateManager::~GameStateManager()
{
	for (auto iter = m_availableState.begin(); iter != m_availableState.end(); ++iter)
	{
		delete iter->second;
	}

	m_availableState.clear();
}

void GameStateManager::updateStates(float deltaTime)
{
	processCommands();

	for (auto iter = m_states.begin(); iter != m_states.end(); iter++)
	{
		(*iter)->update(deltaTime);
	}
}

void GameStateManager::drawGameStates(aie::Renderer2D *renderer)
{
	for (auto iter = m_states.begin(); iter != m_states.end(); iter++)
	{
		(*iter)->draw(renderer);
	}
}

void GameStateManager::setState(const char * name, iGameState * state)
{
	commands cmd;
	cmd.cmd = eCommands::set_state;
	cmd.name = name;
	cmd.state = state;

	m_commands.push_back(cmd);
}

void GameStateManager::pushState(const char * name)
{
	commands cmd;
	cmd.cmd = eCommands::push_state;
	cmd.name = name;

	m_commands.push_back(cmd);
}

void GameStateManager::popState()
{
	commands cmd;
	cmd.cmd = eCommands::pop_state;

	m_commands.push_back(cmd);
}

void GameStateManager::processCommands()
{
	for (auto iter = m_commands.begin(); iter != m_commands.end(); ++iter)
	{
		commands &cmd = (*iter);
		switch (cmd.cmd)
		{
			case eCommands::set_state:dosetState(cmd.name, cmd.state); break;
			case eCommands::push_state:dopushState(cmd.name);  break;
			case eCommands::pop_state:dopopState(); break;
		}
	}
	m_commands.clear();
}

void GameStateManager::dosetState(const char * name, iGameState * state)
{
	auto iter = m_availableState.find(name);
	if (iter != m_availableState.end())
	{
		delete iter->second;
	}

	m_availableState[name] = state;
}

void GameStateManager::dopushState(const char * name)
{
	auto iter = m_availableState.find(name);
	if (iter != m_availableState.end())
	{
		m_states.push_back(iter->second);
	}
}

void GameStateManager::dopopState()
{
	if (m_states.empty())
	{
		return;
	}

	m_states.pop_back();
}
