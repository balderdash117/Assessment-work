#include "keyboardBehaviour.h"
#include <input.h>
#include "GameObject.h"

KeyboardBehaviour::KeyboardBehaviour(int upkey, int rightkey, int downkey, int leftkey) : 
	behaviour(), 
	m_upkey(upkey),
	m_rightkey(rightkey),
	m_downkey(downkey),
	m_leftkey(leftkey),
	m_force(1000)
{
	if (m_upkey == 0) m_upkey = aie::INPUT_KEY_W;
	if (m_rightkey == 0) m_rightkey = aie::INPUT_KEY_D;
	if (m_downkey == 0) m_downkey = aie::INPUT_KEY_S;
	if (m_leftkey == 0) m_leftkey = aie::INPUT_KEY_A;
}

KeyboardBehaviour::~KeyboardBehaviour()
{
}

void KeyboardBehaviour::update(GameObject *object, float deltaTime)
{
	if (aie::Input::getInstance()->isKeyDown(m_upkey))
		object->applyForce(glm::vec2(0, m_force));
	if (aie::Input::getInstance()->isKeyDown(m_downkey))
		object->applyForce(glm::vec2(0, m_force * -1));
	if (aie::Input::getInstance()->isKeyDown(m_rightkey))
		object->applyForce(glm::vec2(m_force, 0));
	if (aie::Input::getInstance()->isKeyDown(m_leftkey))
		object->applyForce(glm::vec2(m_force * -1, 0));
}

int KeyboardBehaviour::getUpKey()
{
	return m_upkey;
}

int KeyboardBehaviour::getRightKey()
{
	return m_rightkey;
}

int KeyboardBehaviour::getDownKey()
{
	return m_downkey;
}

int KeyboardBehaviour::getLeftKey()
{
	return m_leftkey;
}

void KeyboardBehaviour::setUpKey(int key)
{
	m_upkey = key;
}

void KeyboardBehaviour::setRightKey(int key)
{
	m_rightkey = key;
}

void KeyboardBehaviour::setDownKey(int key)
{
	m_downkey = key;
}

void KeyboardBehaviour::setLeftKey(int key)
{
	m_leftkey = key;
}


